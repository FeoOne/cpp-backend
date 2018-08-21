/**
 * @file http_service.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef BACKEND_HTTP_SERVICE_H
#define BACKEND_HTTP_SERVICE_H

#include <engine.h>

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
        engine::web_view_loader::uptr                               _web_view_loader;
        engine::web_view_manager::uptr                              _web_view_manager;

        std::unordered_map<std::string_view,
                std::function<void(engine::http_response::sptr&)>>  _handlers;

        void handle_http_request_task(const engine::task::sptr& t) noexcept;

    };

}

#endif /* BACKEND_HTTP_SERVICE_H */
