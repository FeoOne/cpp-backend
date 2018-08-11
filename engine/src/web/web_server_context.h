/**
 * @file web_server_context.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_EXECUTION_CONTEXT_H
#define ENGINE_WEB_EXECUTION_CONTEXT_H

#include <glib/gstdio.h>
#include <libsoup/soup.h>

#include "core/execution_context.h"

namespace engine {

    class web_server_context final : public execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_context)
        FW_DELETE_ALL_DEFAULT(web_server_context)web_server_context

        static constexpr std::string_view NAME { "web_server" };

        explicit web_server_context(const framework::config_setting::sptr& config) noexcept;
        virtual ~web_server_context();

    private:
        GMainLoop *             _loop;
        SoupServer *            _server;

        void _poll_once() noexcept final;

        void _before_execute() noexcept final;
        void _after_execute() noexcept final;

        bool _should_work() const noexcept final;
        void _should_work(bool b) noexcept final;

        void _create_server() noexcept;
        void _destroy_server() noexcept;

    };

}

#endif /* ENGINE_WEB_EXECUTION_CONTEXT_H */
