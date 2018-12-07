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

        explicit http_client_request(const char *method, const char *uri) noexcept;
        explicit http_client_request(const char *method, SoupURI *uri) noexcept;
        ~http_client_request();

    private:
        SoupMessage *           _message;

    };

}

#endif /* ENGINE_HTTP_CLIENT_REQUEST_H */
