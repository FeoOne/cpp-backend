//
// Created by Feo on 07/12/2018.
//

#include "context/web/task/http_client_request_task.h"

namespace engine {

    http_client_request_task::~http_client_request_task()
    {
        delete _request;
    }

}
