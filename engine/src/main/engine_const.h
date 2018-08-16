/**
 * @file engine_const.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_ENGINE_CONST_H
#define ENGINE_ENGINE_CONST_H

#include <framework.h>

namespace engine {

    class engine_const {
    public:
        static constexpr size_t             TASK_TYPE_MAX_COUNT { 32 };

        static constexpr size_t             WEB_SERVER_PORT { 8888 };
        static constexpr std::string_view   WEB_SERVER_HEADER { "bitpt-httpd" };
        static constexpr std::string_view   WEB_SERVER_DEFAULT_HTTP_ROUTE { "/" };

        static constexpr std::string_view   JOB_CONTEXT_NAME { "job" };
        static constexpr std::string_view   SYSTEM_CONTEXT_NAME { "system" };
        static constexpr std::string_view   WEB_SERVER_CONTEXT_NAME { "web-server" };

    };

}

#endif /* ENGINE_ENGINE_CONST_H */
