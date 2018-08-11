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

namespace engine {

    class web_server_context final : public execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_context)
        FW_DELETE_ALL_DEFAULT(web_server_context)

        explicit web_server_context(const framework::config_setting::sptr& config) noexcept;
        virtual ~web_server_context();

    private:
        SoupServer *        _server;

        void _before_run() noexcept final;
        void _after_run() noexcept final;

        void _create_server() noexcept;
        void _destroy_server() noexcept;

    };

}

#endif /* ENGINE_WEB_EXECUTION_CONTEXT_H */
