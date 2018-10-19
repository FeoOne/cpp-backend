/**
 * @file tcp_service.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_TCP_SERVICE_H
#define ENGINE_TCP_SERVICE_H

#include "work/work_service.h"
#include "context/io/net/timer.h"
#include "context/io/connection/tcp_connection.h"
#include "context/io/task/connection_status_changed_task.h"

namespace engine {

    class tcp_service final : public stl::crucial<work_service, tcp_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(tcp_service)
        STL_DELETE_ALL_DEFAULT(tcp_service)

        explicit tcp_service(const stl::setting& config,
                             task_router *router,
                             const work_service_delegate *delegate) noexcept;

        virtual ~tcp_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

        void add_local_connection(tcp_connection *connection) noexcept;
        void shutdown_connection(tcp_connection *connection) noexcept;

        void write(const connection_link& link,
                   u32 opcode,
                   u8 *memory,
                   size_t length,
                   bool is_urgent) noexcept;

    private:
        std::vector<tcp_connection *>                   _local_connections;
        std::list<tcp_connection *>                     _disconnected_connections;
        timer::uptr                                     _reconnect_timer;
        const std::unordered_map<connection_kind,
                std::function<void(tcp_connection *)>>  _start_callbacks;

        void start_local_connections() noexcept;
        void start_local_master(tcp_connection *connection) noexcept;
        void start_local_slave(tcp_connection *connection) noexcept;

        void change_connection_status(tcp_connection *connection, connection_status status) noexcept;
        void reconnection_cleanup(tcp_connection *connection) noexcept;

        void on_reconnect_timer() noexcept;

        void on_connection(network_handle *handle, int status) noexcept;
        void on_connect(uv_request *request, int status) noexcept;
        void on_alloc(network_handle *handle, size_t suggested_size, uv_buf_t *buffer) noexcept;
        void on_read(network_handle *handle, ssize_t nread, const uv_buf_t *buffer) noexcept;
        void on_write(uv_request *request, int status) noexcept;
        void on_shutdown(uv_request *request, int status) noexcept;
        void on_close(network_handle *handle) noexcept;

        static void connection_callback(uv_stream_t *stream, int status) noexcept;
        static void connect_callback(uv_connect_t *req, int status) noexcept;
        static void alloc_callback(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buffer) noexcept;
        static void read_callback(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buffer) noexcept;
        static void write_callback(uv_write_t *req, int status) noexcept;
        static void shutdown_callback(uv_shutdown_t *req, int status) noexcept;
        static void close_callback(uv_handle_t *handle) noexcept;

    };

}

#endif /* ENGINE_TCP_SERVICE_H */
