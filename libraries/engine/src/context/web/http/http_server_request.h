/**
 * @file http_request.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_REQUEST_H
#define ENGINE_HTTP_REQUEST_H

#include <libsoup/soup.h>

#include <stl.h>

namespace engine {

    class http_server_request {
    public:
        STL_DECLARE_SMARTPOINTERS(http_server_request)
        STL_DELETE_ALL_DEFAULT(http_server_request)

        explicit http_server_request(SoupMessage *message,
                              const std::string_view& path,
                              GHashTable *query,
                              SoupClientContext *client) noexcept;
        ~http_server_request();

        SoupMessage *get_message() noexcept { return _message; }
        const std::string_view& get_path() const { return _path; }

    private:
        SoupMessage *           _message;
        std::string_view        _path;

    };

}

#endif /* ENGINE_HTTP_REQUEST_H */
