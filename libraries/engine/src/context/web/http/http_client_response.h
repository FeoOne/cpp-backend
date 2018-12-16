//
// Created by Feo on 12/12/2018.
//

#ifndef ENGINE_HTTP_CLIENT_RESPONSE_H
#define ENGINE_HTTP_CLIENT_RESPONSE_H

#include <libsoup/soup.h>

#include <stl.h>

namespace engine {

    class http_client_response {
    public:
        STL_DECLARE_SMARTPOINTERS(http_client_response)
        STL_DELETE_ALL_DEFAULT(http_client_response)

        explicit http_client_response(SoupMessage *message) noexcept;

        ~http_client_response();

        u32 status_code() const noexcept;
        SoupMessageBody *request_body() noexcept;
        SoupMessageBody *response_body() noexcept;

    private:
        SoupMessage *       _message;

    };

}

#endif /* ENGINE_HTTP_CLIENT_RESPONSE_H */
