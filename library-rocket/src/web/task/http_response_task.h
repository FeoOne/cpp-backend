/**
 * @file http_response_task.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ROCKET_HTTP_RESPONSE_TASK_H
#define ROCKET_HTTP_RESPONSE_TASK_H

#include "task/task.h"
#include "web/http/http_response.h"

namespace rocket {

    class http_response_task : public groot::crucial<task, http_response_task> {
    public:
        FW_DECLARE_SMARTPOINTERS(http_response_task)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_response_task)

        explicit http_response_task(const http_response::sptr& response) noexcept : _response { response } {}
        virtual ~http_response_task() = default;

        http_response::sptr get_response() const noexcept { return _response; }

    private:
        http_response::sptr     _response;

    };

}

#endif /* ROCKET_HTTP_RESPONSE_TASK_H */
