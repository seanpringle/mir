/*
 * Copyright © 2012 Canonical Ltd.
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
 * Authored by:
 *   Kevin DuBois <kevin.dubois@canonical.com>
 */

#include "mir/graphics/platform.h"
#include "mir/compositor/buffer_properties.h"
#include "android_buffer_allocator.h"
#include "android_alloc_adaptor.h"
#include "android_buffer.h"

#include <stdexcept>

namespace mg  = mir::graphics;
namespace mga = mir::graphics::android;
namespace mc  = mir::compositor;
namespace geom = mir::geometry;


struct AllocDevDeleter
{
    void operator()(alloc_device_t* t)
    {
        /* android takes care of delete for us */
        t->common.close((hw_device_t*)t);
    }
};

mga::AndroidBufferAllocator::AndroidBufferAllocator(std::unique_ptr<mc::BufferIDUniqueGenerator> && generator)
 : id_generator(std::move(generator))
{
    int err;

    err = hw_get_module(GRALLOC_HARDWARE_MODULE_ID, &hw_module);
    if (err < 0)
        throw std::runtime_error("Could not open hardware module");

    struct alloc_device_t* alloc_dev;
    err = hw_module->methods->open(hw_module, GRALLOC_HARDWARE_GPU0, (struct hw_device_t**) &alloc_dev);
    if (err < 0)
        throw std::runtime_error("Could not open hardware module");

    /* note for future use: at this point, the hardware module should be filled with vendor information
       that we can determine different courses of action based upon */

    AllocDevDeleter del;
    std::shared_ptr<struct alloc_device_t> alloc_dev_ptr(alloc_dev, del);
    alloc_device = std::shared_ptr<mga::GraphicAllocAdaptor>(new AndroidAllocAdaptor(alloc_dev_ptr));
}

std::shared_ptr<mc::Buffer> mga::AndroidBufferAllocator::alloc_buffer(
    mc::BufferProperties const& buffer_properties)
{
    auto id = id_generator->generate_unique_id();
    return std::shared_ptr<mc::Buffer>(
        new AndroidBuffer(alloc_device, id,
                          buffer_properties.size,
                          buffer_properties.format));
}
