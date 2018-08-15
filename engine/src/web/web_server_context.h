/**
 * @file web_server_context.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_EXECUTION_CONTEXT_H
#define ENGINE_WEB_EXECUTION_CONTEXT_H

#include <libsoup/soup.h>

#include "core/execution_context.h"
#include "web/web_server_event_queue.h"

namespace engine {

    class web_server_context final : public execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_context)
        FW_DELETE_ALL_DEFAULT(web_server_context)

        explicit web_server_context(const event_queue::sptr& queue,
                                    const event_recipient::sptr& recipient,
                                    const framework::config_setting::sptr& config) noexcept;
        virtual ~web_server_context() = default;

    private:
        SoupServer *        _server;

        void before_run() noexcept final;
        void after_run() noexcept final;

        void _create_server() noexcept;
        void _destroy_server() noexcept;

        void _print_server_info() const noexcept;

        void _create_http_handle_service(const framework::config_setting::sptr& route_config) noexcept;
        void _destroy_http_handle_service() noexcept;

        void _create_websocket_handle_service(const framework::config_setting::sptr& route_config) noexcept;
        void _destroy_websocket_handle_service() noexcept;

    };

}

#endif /* ENGINE_WEB_EXECUTION_CONTEXT_H */
