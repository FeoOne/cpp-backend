/**
 * @file execution_service.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "work/work_service.h"

namespace engine {

    FW_CRUCIAL_BASE_DECLARATION(work_service)

    work_service::work_service(const framework::config_setting::sptr& config,
                               const task_router::sptr& router,
                               const work_service_provider *service_provider) noexcept :
            _config { config },
            _router { router },
            _service_provider { service_provider }
    {
    }

}
