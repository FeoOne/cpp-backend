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

    };

}

#endif /* ENGINE_HTTP_CLIENT_RESPONSE_H */
