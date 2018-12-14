//
// Created by Feo on 12/12/2018.
//

#include "http_client_response_task.h"

namespace engine {

    http_client_response_task::~http_client_response_task()
    {
        delete _response;
    }

    void http_client_response_task::execute_callback() noexcept
    {
        if (_callback) {
            _callback(_response);
        }
    }

}
