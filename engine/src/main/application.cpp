/**
 * @file application.cpp
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#include <framework.h>

#include "main/application.h"

namespace engine {

    using namespace framework;

    application::application()
    {
        log_manager::setup();
    }

    application::~application()
    {

    }

}
