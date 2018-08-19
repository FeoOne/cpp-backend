/**
 * @file http_request_task.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_REQUEST_TASK_H
#define ENGINE_HTTP_REQUEST_TASK_H

#include "task/task.h"
#include "web/http/http_request.h"

namespace engine {

    class http_request_task : public framework::crucial<task, http_request_task> {
    public:
        FW_DECLARE_SMARTPOINTERS(http_request_task)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_request_task)

        explicit http_request_task(const http_request::sptr& request) noexcept : _request { request } {}
        virtual ~http_request_task() = default;

        http_request::sptr get_request() const noexcept { return _request; }

    private:
        http_request::sptr      _request;

    };

}

#endif /* ENGINE_HTTP_REQUEST_TASK_H */
