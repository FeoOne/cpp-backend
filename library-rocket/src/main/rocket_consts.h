/**
 * @file engine_const.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ROCKET_ROCKET_CONST_H
#define ROCKET_ROCKET_CONST_H

#include <groot.h>

namespace rocket {

    class consts {
    public:
        static constexpr size_t             TASK_TYPE_MAX_COUNT { 32 };
        static constexpr size_t             WORK_CONTEXT_TYPE_MAX_COUNT { 8 };
        static constexpr size_t             WORK_SERVICE_TYPE_MAX_COUNT { 16 };

        static constexpr size_t             WEB_SERVER_PORT { 8888 };
        static constexpr std::string_view   WEB_SERVER_HEADER { " bitpayments-httpd" };
        static constexpr std::string_view   WEB_SERVER_DEFAULT_HTTP_ROUTE { "/" };

        static constexpr std::string_view   WORKER_NAME_IO { "io" };
        static constexpr std::string_view   WORKER_NAME_JOB { "job" };
        static constexpr std::string_view   WORKER_NAME_SYSTEM { "system" };
        static constexpr std::string_view   WORKER_NAME_WEBSERVER { "webserver" };

        static constexpr std::string_view   CONFIG_KEY_WORKERS { "workers" };
        static constexpr std::string_view   CONFIG_KEY_NAME { "name" };
        static constexpr std::string_view   CONFIG_KEY_WEBSERVER_VIEW_ROOT { "view_root" };
        static constexpr std::string_view   CONFIG_KEY_LISTEN { "listen" };
        static constexpr std::string_view   CONFIG_WEBSERVER_LISTEN_ALL { "all" };
        static constexpr std::string_view   CONFIG_WEBSERVER_LISTEN_LOCAL { "local" };

        static constexpr std::string_view   DOMAIN_TASK_QUEUE_JOB { "com.queue.job" };
        static constexpr std::string_view   DOMAIN_TASK_QUEUE_SYSTEM { "com.queue.system" };
        static constexpr std::string_view   DOMAIN_TASK_QUEUE_WEBSERVER { "com.queue.webserver" };

        static constexpr std::string_view   MIME_TYPE_HTML { "text/html" };
        static constexpr std::string_view   MIME_TYPE_JSON { "application/json" };

        static constexpr size_t             CONNECTION_RESERVE_COUNT { 10000 };

    };

}

#endif /* ROCKET_ROCKET_CONST_H */
