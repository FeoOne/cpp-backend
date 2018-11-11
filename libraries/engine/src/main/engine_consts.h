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
                static constexpr const char *session_id { "session_id" };
                static constexpr const char *name { "name" };
                static constexpr const char *path { "path" };
                static constexpr const char *count { "count" };
                static constexpr const char *workers { "workers" };
                static constexpr const char *websocket { "websocket" };
                static constexpr const char *listen { "listen" };
                static constexpr const char *conninfo { "conninfo" };
                static constexpr const char *max_connection_count { "max_connection_count" };
                static constexpr const char *connect_interval { "connect_interval" };
                static constexpr const char *master { "master" };
                static constexpr const char *slave { "slave" };
                static constexpr const char *host { "host" };
                static constexpr const char *port { "port" };
                static constexpr const char *backlog { "backlog" };
                static constexpr const char *keepalive { "keepalive" };
                static constexpr const char *type { "type" };
            };

            /**
             * config::io
             */
            struct io {
                static constexpr const char *tcp { "tcp" };
                static constexpr const char *udp { "udp" };
            };

            /**
             * config::web
             */
             struct web {
                 static constexpr const char *all { "all" };
                 static constexpr const char *local { "local" };
             };

        };

        /**
         * network
         */
        struct net {
            static constexpr size_t read_stream_size { 16384 };
            static constexpr size_t write_stream_size { 16384 };
        };

        /**
         * worker
         */
        struct worker {
            struct name {
                static constexpr const char *io { "io" };
                static constexpr const char *db { "db" };
                static constexpr const char *job { "job" };
                static constexpr const char *web { "web" };
                static constexpr const char *system { "system" };
            };
        };

        /**
         * webserver
         */
        struct webserver {
            static constexpr const char *header { " bitpayments-httpd" };
            static constexpr const char *default_http_route { "/" };
            static constexpr size_t default_http_port { 8888 };
        };












        static constexpr size_t IO_CONNECTION_RESERVE_COUNT { 10000 };





        static constexpr const char *MIME_TYPE_HTML { "text/html" };
        static constexpr const char *MIME_TYPE_JSON { "application/json" };

        static constexpr u32 PROTOCOL_MAGIC { 0x31337FE0 };

    };

}

#endif /* ENGINE_ENGINE_CONST_H */
