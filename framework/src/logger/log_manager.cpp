/**
 * @file log_manager.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "log_manager.h"

namespace framework {

    //static
    void log_manager::setup() noexcept {
        _logger = stdout_logger::make_unique();
    }

}
