/**
 * @file server_service.cpp
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#include "context/web/service/server_service.h"

namespace engine {

    server_service::server_service(const stl::setting& config,
                                         task_router *router,
                                         const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _soup_server { nullptr }
    {
    }

    // virtual
    server_service::~server_service()
    {
    }

    void server_service::setup() noexcept
    {
        GError *error { nullptr };

        auto header { consts::webserver::header };
        if (!config().lookup_string("header", &header)) {
            logwarn("Used default web server header: '%s'.", header);
        }

        auto port { static_cast<s32>(consts::webserver::default_http_port) };
        if (!config().lookup_int32<s32>("port", &port)) {
            logwarn("Used default web server port: '%d'.", port);
        }

        _soup_server = soup_server_new(SOUP_SERVER_SERVER_HEADER, header, nullptr);
        if (_soup_server != nullptr) {
            gboolean result { FALSE };
            auto listen { config()[consts::config::key::listen].to_string() };
            if (STL_IS_STR_EQUAL(listen, consts::config::web::all)) {
                result = soup_server_listen_all(_soup_server,
                                                static_cast<guint>(port),
                                                static_cast<SoupServerListenOptions>(0),
                                                &error);
            } else if (STL_IS_STR_EQUAL(listen, consts::config::web::local)) {
                result = soup_server_listen_local(_soup_server,
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

                soup_server_disconnect(_soup_server);
                _soup_server = nullptr;
            }
        } else {
            logerror("Failed to create web server.");
        }
    }

    void server_service::reset() noexcept
    {
        soup_server_disconnect(_soup_server);
        STL_GOBJECT_RELEASE(_soup_server);
        _soup_server = nullptr;
    }

    void server_service::print_server_info() const noexcept {
        GSList *uris { soup_server_get_uris(_soup_server) };
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
