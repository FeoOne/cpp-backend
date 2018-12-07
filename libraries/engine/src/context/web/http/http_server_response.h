/**
 * @file http_response.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_RESPONSE_H
#define ENGINE_HTTP_RESPONSE_H

#include <stl.h>

#include "context/web/http/http_server_request.h"
#include "context/web/page/web_view.h"

namespace engine {

    class http_server_response {
    public:
        STL_DECLARE_SMARTPOINTERS(http_server_response)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_server_response)

        explicit http_server_response(const http_server_request::sptr& request) noexcept;
        ~http_server_response() = default;

        http_server_request::sptr get_request() const noexcept { return _request; }

        void set_status(SoupStatus status) noexcept;

        void set_view(const web_view::sptr& view) noexcept;

    private:
        http_server_request::sptr      _request;

    };

}

#endif /* ENGINE_HTTP_RESPONSE_H */
