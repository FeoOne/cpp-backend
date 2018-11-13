/**
 * @file http_response_task.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_RESPONSE_TASK_H
#define ENGINE_HTTP_RESPONSE_TASK_H

#include "task/basic_task.h"
#include "context/web/http/http_response.h"

namespace engine {

    class http_response_task : public stl::crucial<basic_task, http_response_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(http_response_task)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_response_task)

        explicit http_response_task(const http_response::sptr& response) noexcept : _response { response } {}
        virtual ~http_response_task() = default;

        http_response::sptr get_response() const noexcept { return _response; }

    private:
        http_response::sptr     _response;

    };

}

#endif /* ENGINE_HTTP_RESPONSE_TASK_H */