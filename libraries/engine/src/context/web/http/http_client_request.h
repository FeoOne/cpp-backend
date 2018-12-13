//
// Created by Feo on 07/12/2018.
//

#ifndef ENGINE_HTTP_CLIENT_REQUEST_H
#define ENGINE_HTTP_CLIENT_REQUEST_H

#include <libsoup/soup.h>

#include <stl.h>

namespace engine {

    class http_client_request {
    public:
        STL_DECLARE_SMARTPOINTERS(http_client_request)
        STL_DELETE_ALL_DEFAULT(http_client_request)

        struct content_type {
            static constexpr char *plain { "text/plain" };
        };

        explicit http_client_request(const char *method, const char *uri) noexcept;
        explicit http_client_request(const char *method, SoupURI *uri) noexcept;
        ~http_client_request();

        void set_body(const char *cont_type, const std::string& data) noexcept;

        SoupMessage *message() noexcept { return _message; }

    private:
        SoupMessage *           _message;

    };

}

#endif /* ENGINE_HTTP_CLIENT_REQUEST_H */
