/**
 * @file engine_const.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ROCKET_ROCKET_CONST_H
#define ROCKET_ROCKET_CONST_H

#include <groot.h>

#define RC_TASK_TYPE_MAX_KEY_COUNT              32
#define RC_WORK_SERVICE_TYPE_MAX_KEY            16
#define RC_WORK_CONTEXT_TYPE_MAX_KEY_COUNT      8

#define RC_IO_BUFFER_SIZE                       4096

//static constexpr std::string_view  { "" };

namespace rocket {

    struct consts { GR_DELETE_ALL_DEFAULT(consts)

        /**
         * config
         */
        struct config { GR_DELETE_ALL_DEFAULT(config)

            /**
             * config::key
             */
            struct key { GR_DELETE_ALL_DEFAULT(key)

                static constexpr std::string_view NAME { "name" };
                static constexpr std::string_view PATH { "path" };
                static constexpr std::string_view COUNT { "count" };
                static constexpr std::string_view WORKERS { "workers" };
                static constexpr std::string_view WEBSOCKET { "websocket" };
                static constexpr std::string_view LISTEN { "listen" };
                static constexpr std::string_view CONNINFO { "conninfo" };
                static constexpr std::string_view MAX_CONNECTION_COUNT { "max_connection_count" };
                static constexpr std::string_view CONNECT_INTERVAL { "connect_interval" };
                static constexpr std::string_view SERVERS { "servers" };
                static constexpr std::string_view CLIENTS { "clients" };
                static constexpr std::string_view HOST { "host" };
                static constexpr std::string_view PORT { "port" };
                static constexpr std::string_view BACKLOG { "backlog" };
                static constexpr std::string_view KEEPALIVE { "keepalive" };
                static constexpr std::string_view TYPE { "type" };
                static constexpr std::string_view INPUT_BUFFER_SIZE { "input_buffer_size" };
                static constexpr std::string_view OUTPUT_BUFFER_SIZE { "output_buffer_size" };

            };

            /**
             * config::io
             */
            struct io { GR_DELETE_ALL_DEFAULT(io)

                static constexpr std::string_view TCP { "tcp" };
                static constexpr std::string_view UDP { "udp" };

            };

            /**
             * config::web
             */
             struct web { GR_DELETE_ALL_DEFAULT(web)

                 static constexpr std::string_view ALL { "all" };
                 static constexpr std::string_view LOCAL { "local" };

             };

        };







        static constexpr std::string_view   WORKER_NAME_IO { "io" };
        static constexpr std::string_view   WORKER_NAME_DB { "db" };
        static constexpr std::string_view   WORKER_NAME_JOB { "job" };
        static constexpr std::string_view   WORKER_NAME_WEB { "web" };
        static constexpr std::string_view   WORKER_NAME_SYSTEM { "system" };

        static constexpr std::string_view   WEB_WEBSERVER_HEADER { " bitpayments-httpd" };
        static constexpr size_t             WEB_DEFAULT_HTTP_PORT { 8888 };
        static constexpr std::string_view   WEB_DEFAULT_HTTP_ROUTE { "/" };

        static constexpr size_t             IO_CONNECTION_RESERVE_COUNT { 10000 };



        static constexpr std::string_view   DOMAIN_TASK_QUEUE_JOB { "com.queue.job" };
        static constexpr std::string_view   DOMAIN_TASK_QUEUE_SYSTEM { "com.queue.system" };
        static constexpr std::string_view   DOMAIN_TASK_QUEUE_WEBSERVER { "com.queue.webserver" };

        static constexpr std::string_view   MIME_TYPE_HTML { "text/html" };
        static constexpr std::string_view   MIME_TYPE_JSON { "application/json" };

        static constexpr u32                PROTOCOL_MAGIC { 0x31337FE0 };

    };

}

#endif /* ROCKET_ROCKET_CONST_H */
