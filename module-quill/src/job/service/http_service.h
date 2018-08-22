/**
 * @file http_service.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef QUILL_HTTP_SERVICE_H
#define QUILL_HTTP_SERVICE_H

#include <rocket.h>

#include "main/quill_consts.h"

#define RC_DEFINE_ACTION(name, ver) \
    rocket::http_response::sptr action_##name##_##ver(const rocket::http_request::sptr& request) noexcept

namespace quill {

    class http_service final : public groot::crucial<rocket::work_service, http_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(http_service)
        GR_DELETE_ALL_DEFAULT(http_service)

        explicit http_service(const groot::config_setting::sptr& config,
                              const rocket::task_router::sptr& router,
                              const rocket::work_context_delegate *service_provider) noexcept;
        virtual ~http_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        using action = std::function<rocket::http_response::sptr(const rocket::http_request::sptr&)>;

        rocket::web_view_loader::uptr                       _web_view_loader;
        rocket::web_view_manager::uptr                      _web_view_manager;

        std::unordered_map<std::string_view, action>        _actions;

        void handle_http_request_task(const rocket::task::sptr& t) noexcept;

        RC_DEFINE_ACTION(invoice, v1);

    };

}

#undef RC_DEFINE_ACTION

#endif /* QUILL_HTTP_SERVICE_H */
