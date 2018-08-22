/**
 * @file http_service.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/http_service.h"

#define RC_DECLARE_ACTION(name, ver)         \
    rocket::http_response::sptr         \
    http_service::action_##name##_##ver(const rocket::http_request::sptr& request) noexcept

#define RC_ADD_ACTION(path, name, ver)          \
    _actions.insert({ { "/api/" GR_STR(ver) "/" path }, \
        std::bind(&http_service::action_##name##_##ver, this, std::placeholders::_1) })

namespace quill {

    http_service::http_service(const groot::config_setting::sptr& config,
                               const rocket::task_router::sptr& router,
                               const rocket::work_context_delegate *service_provider) noexcept :
            crucial(config, router, service_provider),
            _web_view_loader {
                    rocket::web_view_loader::make_unique(
                            (*(*config->root())["web"])["view_root"]->to_string_view()
                            )
            },
            _web_view_manager { rocket::web_view_manager::make_unique() }
    {
        RC_BIND_TASK_HANDLER(rocket::http_request_task, http_service, handle_http_request_task);
    }

    // virtual
    http_service::~http_service()
    {
    }

    // virtual
    void http_service::setup() noexcept
    {
        RC_ADD_ACTION("invoice", invoice, v1);
    }

    // virtual
    void http_service::reset() noexcept
    {
        _actions.clear();
    }

    void http_service::handle_http_request_task(const rocket::task::sptr& t) noexcept
    {
        auto task = std::static_pointer_cast<rocket::http_request_task>(t);
        auto request = task->get_request();
        rocket::http_response::sptr response { nullptr };

        auto it = _actions.find(request->get_path());
        if (it != _actions.end()) {
            response = it->second(request);
        } else {
            logerror("Failed to process path: '%s'.", request->get_path().data());
        }

        get_router()->enqueue(rocket::http_response_task::make_shared(response));
    }

    RC_DECLARE_ACTION(invoice, v1)
    {
        auto response = rocket::http_response::make_shared(request);

        auto root = _web_view_loader->load("layout/base.html");
        auto body = _web_view_loader->load("invoice/body.html");
        auto style = _web_view_loader->load("style/style.css");

        if (root && body && style) {
            root->set_argument("TITLE", "bitpayments - invoice");
            root->set_argument("STYLE", style);
            root->set_argument("BODY", body);

            response->set_status(SOUP_STATUS_OK);
            response->set_view(root);
        } else {
            logerror("Failed to process action: '%s'.", request->get_path().data());
            response->set_status(SOUP_STATUS_INTERNAL_SERVER_ERROR);
        }

        return response;
    }

}

#undef RC_DECLARE_ACTION
#undef RC_ADD_ACTION
