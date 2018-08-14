/**
 * @file web_server_service.h
 * @author Feo
 * @date 14/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_SERVER_SERVICE_H
#define ENGINE_WEB_SERVER_SERVICE_H

#include <libsoup/soup.h>

#include "web/go_memory.h"
#include "core/execution_service.h"

#define WEB_SERVER_SERVICE_BASE     framework::crucial<execution_service, T>

namespace engine {

    template<typename T>
    class web_server_service : public WEB_SERVER_SERVICE_BASE {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_service<T>)
        FW_DELETE_ALL_DEFAULT(web_server_service)

        using derived_type = typename WEB_SERVER_SERVICE_BASE::derived_type;

        virtual ~web_server_service() {
            GO_UNREF(_server);
        }

    protected:
        explicit web_server_service(const event_router::sptr& router, SoupServer *server) noexcept :
                WEB_SERVER_SERVICE_BASE(router),
                _server { GO_REF(server) }
        {}

        SoupServer *get_server() noexcept { return _server; }

    private:
        SoupServer *        _server;

    };

}

#undef WEB_SERVER_SERVICE_BASE

#endif /* ENGINE_WEB_SERVER_SERVICE_H */
