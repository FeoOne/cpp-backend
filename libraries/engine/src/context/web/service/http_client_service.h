//
// Created by Feo on 07/12/2018.
//

#ifndef ENGINE_HTTP_CLIENT_SERVICE_H
#define ENGINE_HTTP_CLIENT_SERVICE_H

#include <libsoup/soup.h>

#include "work/service/work_service.h"
#include "context/web/task/http_client_request_task.h"
#include "context/web/task/http_client_response_task.h"

namespace engine {

    /**
     * HTTP client service is for making HTTP requests.
     * This class represents nonblocking CURL analogue.
     */
    class http_client_service : public stl::crucial<work_service, http_client_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(http_client_service)
        STL_DELETE_ALL_DEFAULT(http_client_service)

        explicit http_client_service(const stl::setting& config,
                                     task_router *router,
                                     const work_service_delegate *delegate) noexcept;
        virtual ~http_client_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        struct request_context {
            http_client_service *                       service;
            http_client_request_task::response_callback callback;
        };

        SoupSession *                                               _session;
        std::unordered_map<SoupMessage *, http_client_request *>    _requests;
        stl::fixed_memory_pool::uptr                                _request_pool;

        void setup_soup_session() noexcept;
        void reset_soup_session() noexcept;

        void handle_http_client_request_task(basic_task *base_task) noexcept;

        void on_handler(SoupSession *session, SoupMessage *message, request_context *context) noexcept;

        static void handler_callback(SoupSession *session, SoupMessage *message, gpointer user_data) noexcept;

    };

}

#endif /* ENGINE_HTTP_CLIENT_SERVICE_H */
