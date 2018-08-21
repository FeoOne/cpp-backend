/**
 * @file http_response.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ROCKET_HTTP_RESPONSE_H
#define ROCKET_HTTP_RESPONSE_H

#include <groot.h>

#include "web/http/http_request.h"
#include "web/page/web_view.h"

namespace rocket {

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

#endif /* ROCKET_HTTP_RESPONSE_H */
