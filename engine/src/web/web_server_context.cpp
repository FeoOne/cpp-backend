/**
 * @file web_server_context.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */


#include "events/events.h"
#include "main/engine_const.h"
#include "web/web_server_loop.h"
#include "web/service/http_handle_service.h"
#include "web/service/websocket_handle_service.h"

#include "web/web_server_context.h"

namespace engine {

    using namespace framework;

    web_server_context::web_server_context(const event_queue::sptr &queue,
                                           const event_router::sptr &router,
                                           const config_setting::sptr &config) noexcept :
            execution_context(web_server_loop::make_unique(queue), queue, router, config),
            _server{nullptr} {
    }

    // virtual
    web_server_context::~web_server_context() {
    }

    // virtual
    void web_server_context::_before_run() noexcept {
        _create_server();
        _create_http_handle_service();
        _create_websocket_handle_service();
    }

    // virtual
    void web_server_context::_after_run() noexcept {
        _destroy_websocket_handle_service();
        _destroy_http_handle_service();
        _destroy_server();
    }

    void web_server_context::_create_server() noexcept {
        GError *error{nullptr};

        const char *header = engine_const::WEB_SERVER_HEADER.data();
        if (!config()->lookup_string("header", &header)) {
            logwarn("Used default web server header: '%s'.", header);
        }

        s32 port = static_cast<s32>(engine_const::WEB_SERVER_PORT);
        if (!config()->lookup_s32("port", &port)) {
            logwarn("Used default web server port: '%d'.", port);
        }

        _server = soup_server_new(SOUP_SERVER_SERVER_HEADER, header, nullptr);
        if (_server != nullptr) {
            auto result = soup_server_listen_all(_server,
                                                 static_cast<guint>(port),
                                                 static_cast<SoupServerListenOptions>(0),
                                                 &error);

            if (result == TRUE) {
                _print_server_info();
                loginfo("Web server started...");
            } else {
                logerror("Failed to start web server.");

                soup_server_disconnect(_server);
                _server = nullptr;
            }
        } else {
            logerror("Failed to create web server.");
        }
    }

    void web_server_context::_destroy_server() noexcept {
        if (_server != nullptr) {
            soup_server_disconnect(_server);
            _server = nullptr;
        }
    }

    void web_server_context::_print_server_info() const noexcept {
        GSList *uris{soup_server_get_uris(_server)};
        for (GSList *u = uris; u != nullptr; u = u->next) {
            auto suri{reinterpret_cast<SoupURI *>(u->data)};
            char *str{soup_uri_to_string(suri, FALSE)};
            loginfo("Listening on %s", str);
            g_free(str);
            soup_uri_free(suri);
        }
        g_slist_free(uris);
    }

    void web_server_context::_create_http_handle_service() noexcept {
        auto service{http_handle_service::make_shared(_server)};
        _add_service(service);

        auto route_config = (*config())["route"];

        for (size_t i = 0; i < route_config->size(); ++i) {
            auto cfg{(*route_config)[i]};
            std::string_view type{(*cfg)["type"]->to_string()};
            if (type == engine_const::WEB_SERVER_HTTP_HANDLE) {
                auto handler{http_request_handler};
                service->add
            }
        }
    }

    void web_server_context::_destroy_http_handle_service() noexcept {
        _remove_service(http_handle_service::key());
    }

    void web_server_context::_create_websocket_handle_service() noexcept {
        auto service = websocket_handle_service::make_shared(_server);
        _add_service(service);
    }

    void web_server_context::_destroy_websocket_handle_service() noexcept {
        _remove_service(websocket_handle_service::key());
    }

}
