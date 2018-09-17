/**
 * @file http_request.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ROCKET_HTTP_REQUEST_H
#define ROCKET_HTTP_REQUEST_H

#include <libsoup/soup.h>

#include <groot.h>

namespace rocket {

    class http_request {
    public:
        GR_DECLARE_SMARTPOINTERS(http_request)
        GR_DELETE_ALL_DEFAULT(http_request)

        explicit http_request(SoupMessage *message,
                              const std::string_view& path,
                              GHashTable *query,
                              SoupClientContext *client) noexcept;
        ~http_request();

        SoupMessage *get_message() noexcept { return _message; }
        const std::string_view& get_path() const { return _path; }

    private:
        SoupMessage *           _message;
        std::string_view        _path;

    };

}

#endif /* ROCKET_HTTP_REQUEST_H */
