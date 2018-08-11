/**
 * @file web_server_context.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "web/web_server_context.h"

namespace engine {

    using namespace framework;

    web_server_context::web_server_context(const config_setting::sptr& config) noexcept :
            execution_context(config),
            _loop { nullptr },
            _server { nullptr }
    {
    }

    // virtual
    web_server_context::~web_server_context()
    {
    }

    // virtual
    void web_server_context::_poll_once() noexcept
    {
        if (_loop == nullptr) {
            _loop = g_main_loop_new(nullptr, TRUE);
            g_main_loop_run(_loop);
        } else {
            logerror("Failed to poll already polled web loop.");
        }
    }

    // virtual
    void web_server_context::_before_execute() noexcept
    {
        _create_server();
    }

    // virtual
    void web_server_context::_after_execute() noexcept
    {
        _destroy_server();
    }

    // virtual
    bool web_server_context::_should_work() const noexcept
    {
        return false;
    }

    // virtual
    void web_server_context::_should_work(bool b) noexcept
    {
        if (!b && _loop != nullptr && g_main_loop_is_running(_loop)) {
            g_main_loop_quit(_loop);
            // @todo Does we might unref loop here?
            _loop = nullptr;
        }
    }

    void web_server_context::_create_server() noexcept
    {
        GError *error { nullptr };

        const char *header = (*config())["header"]->to_string();
        s32 port = (*config())["port"]->to_s32();

        _server = soup_server_new(SOUP_SERVER_SERVER_HEADER, header, nullptr);
        if (_server != nullptr) {
            auto result = soup_server_listen_all(_server,
                                                 static_cast<guint>(port),
                                                 static_cast<SoupServerListenOptions>(0),
                                                 &error);
            if (result == TRUE) {
                GSList *uris = soup_server_get_uris(_server);
                for (GSList *u = uris; u != nullptr; u = u->next) {
                    auto suri = reinterpret_cast<SoupURI *>(u->data);
                    char *str = soup_uri_to_string(suri, FALSE);
                    loginfo("Listening on %s", str);
                    g_free(str);
                    soup_uri_free(suri);
                }
                g_slist_free(uris);

                loginfo("Web server started...");
            } else {
                logerror("Failed to start listen.");
            }
        } else {
            logerror("Failed to create web server.");
        }
    }

    void web_server_context::_destroy_server() noexcept
    {
        if (_server != nullptr) {
            soup_server_disconnect(_server);
            _server = nullptr;
        }
    }

}
