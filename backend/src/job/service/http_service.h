/**
 * @file http_service.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef BACKEND_HTTP_SERVICE_H
#define BACKEND_HTTP_SERVICE_H

#include <engine.h>

#define EG_DEFINE_ACTION(name) \
    engine::http_response::sptr action_##name(const engine::http_request::sptr& request) noexcept

namespace backend {

    class http_service final : public framework::crucial<engine::work_service, http_service> {
    public:
        FW_DECLARE_SMARTPOINTERS(http_service)
        FW_DELETE_ALL_DEFAULT(http_service)

        explicit http_service(const framework::config_setting::sptr& config,
                              const engine::task_router::sptr& router,
                              const engine::work_context_delegate *service_provider) noexcept;
        virtual ~http_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        using action = std::function<engine::http_response::sptr(const engine::http_request::sptr&)>;

        engine::web_view_loader::uptr                       _web_view_loader;
        engine::web_view_manager::uptr                      _web_view_manager;

        std::unordered_map<std::string_view, action>        _actions;

        void handle_http_request_task(const engine::task::sptr& t) noexcept;

        EG_DEFINE_ACTION(not_found);
        EG_DEFINE_ACTION(index);
        EG_DEFINE_ACTION(invoice);

    };

}

#undef EG_DEFINE_ACTION

#endif /* BACKEND_HTTP_SERVICE_H */
