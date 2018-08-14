/**
 * @file execution_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "core/execution_service.h"

namespace engine {

    FW_CRUCIAL_BASE_DECLARATION(execution_service)

    execution_service::execution_service(const event_router::sptr& router) noexcept :
            _router { router }
    {
    }

}
