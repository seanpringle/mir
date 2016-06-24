/*
 * Copyright © 2015 Canonical Ltd.
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
 * Authored by: Cemil Azizoglu <cemil.azizoglu@canonical.com>
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "src/platforms/mesa/server/x11/graphics/display.h"
#include "mir/test/doubles/mock_egl.h"
#include "mir/test/doubles/mock_x11.h"
#include "mir/test/doubles/mock_gl_config.h"

namespace mg=mir::graphics;
namespace mgx=mg::X;
namespace mtd=mir::test::doubles;
namespace geom=mir::geometry;

namespace
{

geom::Size const size{1280, 1024};

class X11DisplayTest : public ::testing::Test
{
public:

    X11DisplayTest()
    {
        using namespace testing;
        EGLint const client_version = 2;

        ON_CALL(mock_egl, eglQueryContext(mock_egl.fake_egl_display,
                                          mock_egl.fake_egl_context,
                                          EGL_CONTEXT_CLIENT_VERSION,
                                          _))
            .WillByDefault(DoAll(SetArgPointee<3>(client_version),
                            Return(EGL_TRUE)));

        ON_CALL(mock_egl, eglQuerySurface(mock_egl.fake_egl_display,
                                          mock_egl.fake_egl_surface,
                                          EGL_WIDTH,
                                          _))
            .WillByDefault(DoAll(SetArgPointee<3>(size.width.as_int()),
                            Return(EGL_TRUE)));

        ON_CALL(mock_egl, eglQuerySurface(mock_egl.fake_egl_display,
                                          mock_egl.fake_egl_surface,
                                          EGL_HEIGHT,
                                          _))
            .WillByDefault(DoAll(SetArgPointee<3>(size.height.as_int()),
                            Return(EGL_TRUE)));

        ON_CALL(mock_egl, eglGetConfigAttrib(mock_egl.fake_egl_display,
                                             _,
                                             _,
                                             _))
            .WillByDefault(DoAll(SetArgPointee<3>(EGL_WINDOW_BIT),
                            Return(EGL_TRUE)));

        ON_CALL(mock_x11, XNextEvent(mock_x11.fake_x11.display,
                                     _))
            .WillByDefault(DoAll(SetArgPointee<1>(mock_x11.fake_x11.expose_event_return),
                       Return(1)));
    }

    std::shared_ptr<mgx::Display> create_display()
    {
        return std::make_shared<mgx::Display>(
                   mock_x11.fake_x11.display,
                   size,
                   mock_gl_config);
    }

    ::testing::NiceMock<mtd::MockEGL> mock_egl;
    ::testing::NiceMock<mtd::MockX11> mock_x11;
    mtd::MockGLConfig mock_gl_config;
};

}

TEST_F(X11DisplayTest, creates_display_successfully)
{
    using namespace testing;

    EXPECT_CALL(mock_egl, eglGetDisplay(mock_x11.fake_x11.display))
        .Times(Exactly(1));

    EXPECT_CALL(mock_x11, XCreateWindow_wrapper(mock_x11.fake_x11.display,_, size.width.as_int(), size.height.as_int(),_,_,_,_,_,_))
        .Times(Exactly(1));

    EXPECT_CALL(mock_egl, eglCreateContext(mock_egl.fake_egl_display,_, EGL_NO_CONTEXT,_))
        .Times(Exactly(1));

    EXPECT_CALL(mock_egl, eglCreateWindowSurface(mock_egl.fake_egl_display,_, mock_x11.fake_x11.window, nullptr))
        .Times(Exactly(1));

    EXPECT_CALL(mock_x11, XNextEvent(mock_x11.fake_x11.display,_))
        .Times(AtLeast(1));

    EXPECT_CALL(mock_x11, XMapWindow(mock_x11.fake_x11.display,_))
        .Times(Exactly(1));

    auto display = create_display();
}

TEST_F(X11DisplayTest, respects_gl_config)
{
    using namespace testing;

    EGLint const depth_bits{24};
    EGLint const stencil_bits{8};

    EXPECT_CALL(mock_gl_config, depth_buffer_bits())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(depth_bits));
    EXPECT_CALL(mock_gl_config, stencil_buffer_bits())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(stencil_bits));

    EXPECT_CALL(mock_egl,
                eglChooseConfig(
                    _,
                    AllOf(mtd::EGLConfigContainsAttrib(EGL_DEPTH_SIZE, depth_bits),
                          mtd::EGLConfigContainsAttrib(EGL_STENCIL_SIZE, stencil_bits)),
                    _,_,_))
        .Times(AtLeast(1));

    auto display = create_display();
}
