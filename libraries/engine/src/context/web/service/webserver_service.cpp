/**
 * @file webserver_service.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "context/web/service/webserver_service.h"

namespace engine {

    webserver_service::webserver_service(const stl::setting& config,
                                         task_router *router,
                                         const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _server { nullptr }
    {
    }

    // virtual
    webserver_service::~webserver_service()
    {
    }

    void webserver_service::setup() noexcept
    {
        GError *error { nullptr };

        auto header { consts::WEB_WEBSERVER_HEADER.data() };
        if (!config().lookup_string("header", &header)) {
            logwarn("Used default web server header: '%s'.", header);
        }

        auto port { static_cast<s32>(consts::WEB_DEFAULT_HTTP_PORT) };
        if (!config().lookup_int32<s32>("port", &port)) {
            logwarn("Used default web server port: '%d'.", port);
        }

        _server = soup_server_new(SOUP_SERVER_SERVER_HEADER, header, nullptr);
        if (_server != nullptr) {
            gboolean result { FALSE };
            auto listen { config()[consts::config::key::LISTEN].to_string() };
            if (listen == consts::config::web::ALL) {
                result = soup_server_listen_all(_server,
                                                static_cast<guint>(port),
                                                static_cast<SoupServerListenOptions>(0),
                                                &error);
            } else if (listen == consts::config::web::LOCAL) {
                result = soup_server_listen_local(_server,
                                                  static_cast<guint>(port),
                                                  static_cast<SoupServerListenOptions>(0),
                                                  &error);
            } else {
                // @todo Implement parse custom address and listen it.
            }

            if (result == TRUE) {
                print_server_info();
                loginfo("Web server started...");
            } else {
                if (error != nullptr) {
                    logerror("%s", error->message);
                }
                logcrit("Failed to start web server.");

                soup_server_disconnect(_server);
                _server = nullptr;
            }
        } else {
            logerror("Failed to create web server.");
        }
    }

    void webserver_service::reset() noexcept
    {
        soup_server_disconnect(_server);
        STL_GOBJECT_RELEASE(_server);
        _server = nullptr;
    }

    void webserver_service::print_server_info() const noexcept {
        GSList *uris { soup_server_get_uris(_server) };
        for (GSList *u { uris }; u != nullptr; u = u->next) {
            auto suri { reinterpret_cast<SoupURI *>(u->data) };
            char *str { soup_uri_to_string(suri, FALSE) };
            loginfo("Listening on %s", str);
            g_free(str);
            soup_uri_free(suri);
        }
        g_slist_free(uris);
    }

}
