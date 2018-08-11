/**
 * @file http_request_handler.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_REQUEST_HANDLER_H
#define ENGINE_HTTP_REQUEST_HANDLER_H

#include "web/http/http_request.h"
#include "web/http/http_response.h"

namespace engine {

    class http_request_handler {
    public:
        FW_DECLARE_SMARTPOINTERS(http_request_handler)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_request_handler)

        virtual ~http_request_handler() = default;

        virtual http_response::sptr handle(const http_request::sptr& request) noexcept = 0;

    protected:
        http_request_handler() = default;

    };

}

#endif /* ENGINE_HTTP_REQUEST_HANDLER_H */
