/**
 * @file http_request.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_REQUEST_H
#define ENGINE_HTTP_REQUEST_H

#include <libsoup/soup.h>

#include <framework.h>

namespace engine {

    class http_request {
    public:
        FW_DECLARE_SMARTPOINTERS(http_request)
        FW_DELETE_ALL_DEFAULT(http_request)

        explicit http_request(SoupMessage *message,
                              const std::string_view& path,
                              GHashTable *query,
                              SoupClientContext *client) noexcept;
        ~http_request();

    private:

    };

}

#endif /* ENGINE_HTTP_REQUEST_H */
