//
// Created by Feo on 12/12/2018.
//

#ifndef ENGINE_HTTP_CLIENT_RESPONSE_TASK_H
#define ENGINE_HTTP_CLIENT_RESPONSE_TASK_H

#include "task/basic_task.h"
#include "context/web/http/http_client_response.h"

namespace engine {

    class http_client_response_task : public stl::crucial<basic_task, http_client_response_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(http_client_response_task)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_client_response_task)

    };

}

#endif //PROJECT_HTTP_CLIENT_RESPONSE_TASK_H
