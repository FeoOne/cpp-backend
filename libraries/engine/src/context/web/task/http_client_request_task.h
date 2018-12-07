//
// Created by Feo on 07/12/2018.
//

#ifndef ENGINE_HTTP_CLIENT_REQUEST_TASK_H
#define ENGINE_HTTP_CLIENT_REQUEST_TASK_H

#include "task/basic_task.h"
#include "context/web/http/http_client_request.h"

namespace engine {

    class http_client_request_task : public stl::crucial<basic_task, http_client_request_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(http_client_request_task)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_client_request_task)

        explicit http_client_request_task(http_client_request *request) noexcept :
                _request { request }
        {}

        virtual ~http_client_request_task() = default;

        http_client_request *request() noexcept { return _request; }

    private:
        http_client_request *       _request;

    };

}

#endif /* ENGINE_HTTP_CLIENT_REQUEST_TASK_H */
