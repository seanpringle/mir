/*
 * Copyright © 2012-2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alan Griffiths <alan@octopull.co.uk>
 */

#include "mir_toolkit/mir_client_library.h"

#include "mir_test_doubles/stub_buffer.h"
#include "mir_test_doubles/stub_buffer_allocator.h"
#include "mir_test_doubles/null_platform.h"
#include "mir_test_doubles/null_display.h"
#include "mir_test_doubles/stub_display_buffer.h"

#include "mir_test_framework/stubbed_server_configuration.h"
#include "mir_test_framework/basic_client_server_fixture.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mir_test/gmock_fixes.h"

namespace mc = mir::compositor;
namespace mg = mir::graphics;
namespace geom = mir::geometry;
namespace mf = mir::frontend;
namespace mtf = mir_test_framework;
namespace mtd = mir::test::doubles;

namespace
{
geom::Size const size{640, 480};
MirPixelFormat const format{mir_pixel_format_abgr_8888};
mg::BufferUsage const usage{mg::BufferUsage::hardware};
mg::BufferProperties const buffer_properties{size, format, usage};


class MockGraphicBufferAllocator : public mtd::StubBufferAllocator
{
 public:
    MockGraphicBufferAllocator()
    {
        using testing::_;
        ON_CALL(*this, alloc_buffer(_))
            .WillByDefault(testing::Invoke(this, &MockGraphicBufferAllocator::on_create_swapper));
    }

    MOCK_METHOD1(
        alloc_buffer,
        std::shared_ptr<mg::Buffer> (mg::BufferProperties const&));


    std::shared_ptr<mg::Buffer> on_create_swapper(mg::BufferProperties const&)
    {
        return std::make_shared<mtd::StubBuffer>(::buffer_properties);
    }

    ~MockGraphicBufferAllocator() noexcept {}
};

class StubDisplay : public mtd::NullDisplay
{
public:
    StubDisplay()
        : display_buffer{geom::Rectangle{geom::Point{0,0}, geom::Size{1600,1600}}}
    {
    }

    void for_each_display_buffer(std::function<void(mg::DisplayBuffer&)> const& f) override
    {
        f(display_buffer);
    }

private:
    mtd::StubDisplayBuffer display_buffer;
};

struct SurfaceSync
{
    void surface_created(MirSurface * new_surface)
    {
        std::unique_lock<std::mutex> lock(guard);
        surface = new_surface;
        wait_condition.notify_all();
    }

    void surface_released(MirSurface * /*released_surface*/)
    {
        std::unique_lock<std::mutex> lock(guard);
        surface = NULL;
        wait_condition.notify_all();
    }

    void wait_for_surface_create()
    {
        std::unique_lock<std::mutex> lock(guard);
        wait_condition.wait(lock, [&]{ return !!surface; });
    }

    void wait_for_surface_release()
    {
        std::unique_lock<std::mutex> lock(guard);
        wait_condition.wait(lock, [&]{ return !surface; });
    }

    std::mutex guard;
    std::condition_variable wait_condition;
    MirSurface * surface{nullptr};
};

void create_surface_callback(MirSurface* surface, void * context)
{
    SurfaceSync* config = reinterpret_cast<SurfaceSync*>(context);
    config->surface_created(surface);
}

void release_surface_callback(MirSurface* surface, void * context)
{
    SurfaceSync* config = reinterpret_cast<SurfaceSync*>(context);
    config->surface_released(surface);
}

void wait_for_surface_create(SurfaceSync* context)
{
    context->wait_for_surface_create();
}

void wait_for_surface_release(SurfaceSync* context)
{
    context->wait_for_surface_release();
}

struct BufferCounterConfig : mtf::StubbedServerConfiguration
{
    class CountingStubBuffer : public mtd::StubBuffer
    {
    public:

        CountingStubBuffer()
        {
            int created = buffers_created.load();
            while (!buffers_created.compare_exchange_weak(created, created + 1)) std::this_thread::yield();
        }
        ~CountingStubBuffer()
        {
            int destroyed = buffers_destroyed.load();
            while (!buffers_destroyed.compare_exchange_weak(destroyed, destroyed + 1)) std::this_thread::yield();
        }

        static std::atomic<int> buffers_created;
        static std::atomic<int> buffers_destroyed;
    };

    class StubGraphicBufferAllocator : public mtd::StubBufferAllocator
    {
     public:
        std::shared_ptr<mg::Buffer> alloc_buffer(mg::BufferProperties const&) override
        {
            return std::make_shared<CountingStubBuffer>();
        }
    };

    class StubPlatform : public mtd::NullPlatform
    {
    public:
        std::shared_ptr<mg::GraphicBufferAllocator> create_buffer_allocator(
            const std::shared_ptr<mg::BufferInitializer>& /*buffer_initializer*/) override
        {
            return std::make_shared<StubGraphicBufferAllocator>();
        }

        std::shared_ptr<mg::Display> create_display(
            std::shared_ptr<mg::DisplayConfigurationPolicy> const&,
            std::shared_ptr<mg::GLProgramFactory> const&,
            std::shared_ptr<mg::GLConfig> const&) override
        {
            return std::make_shared<StubDisplay>();
        }
    };

    std::shared_ptr<mg::Platform> the_graphics_platform()
    {
        if (!platform)
            platform = std::make_shared<StubPlatform>();

        return platform;
    }

    std::shared_ptr<mg::Platform> platform;
};

std::atomic<int> BufferCounterConfig::CountingStubBuffer::buffers_created;
std::atomic<int> BufferCounterConfig::CountingStubBuffer::buffers_destroyed;
}

struct SurfaceLoop : mtf::BasicClientServerFixture<BufferCounterConfig>
{
    static const int max_surface_count = 5;
    SurfaceSync ssync[max_surface_count];

    MirSurfaceParameters const request_params
    {
        "Arbitrary surface name",
        640, 480,
        mir_pixel_format_abgr_8888,
        mir_buffer_usage_hardware,
        mir_display_output_id_invalid
    };

    void TearDown() override
    {
        mtf::BasicClientServerFixture<BufferCounterConfig>::TearDown();

        EXPECT_EQ(BufferCounterConfig::CountingStubBuffer::buffers_created.load(),
                  BufferCounterConfig::CountingStubBuffer::buffers_destroyed.load());
    }
};

TEST_F(SurfaceLoop, all_created_buffers_are_destroyed)
{
    for (int i = 0; i != max_surface_count; ++i)
        mir_connection_create_surface(connection, &request_params, create_surface_callback, ssync+i);

    for (int i = 0; i != max_surface_count; ++i)
        wait_for_surface_create(ssync+i);

    for (int i = 0; i != max_surface_count; ++i)
        mir_surface_release(ssync[i].surface, release_surface_callback, ssync+i);

    for (int i = 0; i != max_surface_count; ++i)
        wait_for_surface_release(ssync+i);
}

TEST_F(SurfaceLoop, all_created_buffers_are_destroyed_if_client_disconnects_without_releasing_surfaces)
{
    for (int i = 0; i != max_surface_count; ++i)
        mir_connection_create_surface(connection, &request_params, create_surface_callback, ssync+i);

    for (int i = 0; i != max_surface_count; ++i)
        wait_for_surface_create(ssync+i);
}
