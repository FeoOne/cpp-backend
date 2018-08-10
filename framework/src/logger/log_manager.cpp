/**
 * @file log_manager.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "logger/log_manager.h"

namespace framework {

    // static
    logger::uptr log_manager::_logger;

    // static
    void log_manager::setup() noexcept {
        _logger = stdout_logger::make_unique();
    }

}
