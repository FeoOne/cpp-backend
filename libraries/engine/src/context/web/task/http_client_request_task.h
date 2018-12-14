//
// Created by Feo on 07/12/2018.
//

#ifndef ENGINE_HTTP_CLIENT_REQUEST_TASK_H
#define ENGINE_HTTP_CLIENT_REQUEST_TASK_H

#include "task/basic_task.h"
#include "context/web/http/http_client_request.h"
#include "context/web/http/http_client_response.h"

namespace engine {

    class http_client_request_task : public stl::crucial<basic_task, http_client_request_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(http_client_request_task)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_client_request_task)

        using response_callback = std::function<void(http_client_response *)>;

        explicit http_client_request_task(http_client_request *request, response_callback&& callback) noexcept :
                _request { request },
                _callback { callback }
        {}

        virtual ~http_client_request_task();

        http_client_request *request() noexcept { return _request; }
        response_callback&& grab_callback() noexcept { return std::move(_callback); }

    private:
        http_client_request *       _request;
        response_callback           _callback;

    };

}

#endif /* ENGINE_HTTP_CLIENT_REQUEST_TASK_H */
