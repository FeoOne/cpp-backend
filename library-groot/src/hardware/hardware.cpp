/**
 * @file hardware.cpp
 * @author Feo
 * @date 22/09/2018
 * @brief
 */

#include "logger/log_manager.h"
#include "memory/memory.h"

#include "hardware/hardware.h"

namespace groot {

    // static
    void hardware::print_info() noexcept
    {
        lognotice("HW stats: memory page size: %u.", memory::page_size());
    }

}
