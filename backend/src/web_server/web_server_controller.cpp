/**
 * @file web_server_controller.cpp
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#include "main/backend_const.h"
#include "web_server/invoice_request_handler.h"

#include "web_server/web_server_controller.h"

namespace backend {

    web_server_controller::web_server_controller(const engine::http_handle_service::sptr& http_service) noexcept :
            _http_service { http_service }
    {

    }

    web_server_controller::~web_server_controller()
    {

    }

    void web_server_controller::create() noexcept
    {
        auto handler = invoice_request_handler::make_shared();
        _http_service->add_handler(backend_const::HTTP_INVOICE_PATH, handler);
    }

    void web_server_controller::destroy() noexcept
    {
        _http_service->remove_handler(backend_const::HTTP_INVOICE_PATH);
    }

}
