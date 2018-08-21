/**
 * @file http_service.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "job/service/http_service.h"

#define EG_DECLARE_ACTION(name) \
    engine::http_response::sptr http_service::action_##name(const engine::http_request::sptr& request) noexcept

#define EG_ADD_ACTION(path, name) \
    _actions.insert({ { path }, std::bind(&http_service::action_##name, this, std::placeholders::_1) })

namespace backend {

    http_service::http_service(const framework::config_setting::sptr& config,
                               const engine::task_router::sptr& router,
                               const engine::work_context_delegate *service_provider) noexcept :
            crucial(config, router, service_provider),
            _web_view_loader {
                    engine::web_view_loader::make_unique(
                            (*(*config->root())["web"])["view_root"]->to_string_view()
                            )
            },
            _web_view_manager { engine::web_view_manager::make_unique() }
    {
        EG_BIND_TASK_HANDLER(engine::http_request_task, http_service, handle_http_request_task);
    }

    // virtual
    http_service::~http_service()
    {
    }

    // virtual
    void http_service::setup() noexcept
    {
        EG_ADD_ACTION("/404", not_found);
        EG_ADD_ACTION("/", index);
    }

    // virtual
    void http_service::reset() noexcept
    {
        _actions.clear();
    }

    void http_service::handle_http_request_task(const engine::task::sptr& t) noexcept
    {
        auto task = std::static_pointer_cast<engine::http_request_task>(t);
        auto request = task->get_request();
        engine::http_response::sptr response { nullptr };

        auto it = _actions.find(request->get_path());
        if (it != _actions.end()) {
            response = it->second(request);
        } else {
            response = action_not_found(request);
        }

        get_router()->enqueue(engine::http_response_task::make_shared(response));
    }

    EG_DECLARE_ACTION(not_found)
    {
        auto response = engine::http_response::make_shared(request);



        response->set_status(SOUP_STATUS_NOT_FOUND);
//        response->set_view(view);

        return response;
    }

    EG_DECLARE_ACTION(index)
    {
        auto response = engine::http_response::make_shared(request);

        auto root = _web_view_loader->load("layout/base.html");
        auto body = _web_view_loader->load("index/body.html");

        root->set_argument("TITLE", "bitpayments");
        root->set_argument("BODY", body);

        response->set_status(SOUP_STATUS_OK);
        response->set_view(root);

        return response;
    }

}

#undef EG_DECLARE_ACTION
#undef EG_ADD_ACTION
