/**
 * @file http_response.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_RESPONSE_H
#define ENGINE_HTTP_RESPONSE_H

#include <framework.h>

#include "web/http/http_request.h"
#include "web/view/web_view.h"

namespace engine {

    class http_response {
    public:
        FW_DECLARE_SMARTPOINTERS(http_response)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_response)

        explicit http_response(const http_request::sptr& request) noexcept;
        ~http_response() = default;

        http_request::sptr get_request() const noexcept { return _request; }

        void set_status(SoupStatus status) noexcept;

        void set_view(const web_view::sptr& view) noexcept;

    private:
        http_request::sptr      _request;

    };

}

#endif /* ENGINE_HTTP_RESPONSE_H */
