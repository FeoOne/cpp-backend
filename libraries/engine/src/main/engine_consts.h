/**
 * @file engine_const.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_ENGINE_CONST_H
#define ENGINE_ENGINE_CONST_H

#include <stl.h>

#define EX_TASK_TYPE_MAX_KEY_COUNT              32
#define EX_WORK_SERVICE_TYPE_MAX_KEY            64
#define EX_WORK_CONTEXT_TYPE_MAX_KEY_COUNT      8

namespace engine {

    struct consts {

        /**
         * config
         */
        struct config {
            /**
             * config::key
             */
            struct key {
                static constexpr std::string_view session_id { "session_id" };
                static constexpr std::string_view NAME { "name" };
                static constexpr std::string_view PATH { "path" };
                static constexpr std::string_view COUNT { "count" };
                static constexpr std::string_view WORKERS { "workers" };
                static constexpr std::string_view WEBSOCKET { "websocket" };
                static constexpr std::string_view LISTEN { "listen" };
                static constexpr std::string_view CONNINFO { "conninfo" };
                static constexpr std::string_view MAX_CONNECTION_COUNT { "max_connection_count" };
                static constexpr std::string_view CONNECT_INTERVAL { "connect_interval" };
                static constexpr std::string_view MASTER { "master" };
                static constexpr std::string_view SLAVE { "slave" };
                static constexpr std::string_view HOST { "host" };
                static constexpr std::string_view PORT { "port" };
                static constexpr std::string_view BACKLOG { "backlog" };
                static constexpr std::string_view KEEPALIVE { "keepalive" };
                static constexpr std::string_view TYPE { "type" };
            };

            /**
             * config::io
             */
            struct io {
                static constexpr std::string_view TCP { "tcp" };
                static constexpr std::string_view UDP { "udp" };
            };

            /**
             * config::web
             */
             struct web {
                 static constexpr std::string_view ALL { "all" };
                 static constexpr std::string_view LOCAL { "local" };
             };

        };

        /**
         * network
         */
        struct net {
            static constexpr size_t read_stream_size { 16384 };
            static constexpr size_t write_stream_size { 16384 };
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





        static constexpr std::string_view   MIME_TYPE_HTML { "text/html" };
        static constexpr std::string_view   MIME_TYPE_JSON { "application/json" };

        static constexpr u32                PROTOCOL_MAGIC { 0x31337FE0 };

    };

}

#endif /* ENGINE_ENGINE_CONST_H */
