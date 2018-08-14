/**
 * @file http_request_event.h
 * @author Feo
 * @date 13/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_REQUEST_EVENT_H
#define ENGINE_HTTP_REQUEST_EVENT_H

#include "web/http/http_request.h"
#include "event/event.h"

namespace engine {

    class http_request_event : public framework::crucial<event, http_request_event> {
    public:
        FW_DECLARE_SMARTPOINTERS(http_request_event)
        FW_DELETE_ALL_DEFAULT(http_request_event)

        explicit http_request_event(const http_request::sptr& request) : _request { request } {}
        virtual ~http_request_event() = default;

        http_request::sptr request() const noexcept { return _request; }

    private:
        http_request::sptr          _request;

    };

}

#endif /* ENGINE_HTTP_REQUEST_EVENT_H */
