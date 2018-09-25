/**
 * @file tcp_service.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ROCKET_TCP_SERVICE_H
#define ROCKET_TCP_SERVICE_H

#include "work/work_service.h"
#include "io/connection/tcp_connection.h"
#include "io/connection/connection_manager.h"

namespace rocket {

    class tcp_service final : public groot::crucial<work_service, tcp_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(tcp_service)
        GR_DELETE_ALL_DEFAULT(tcp_service)

        explicit tcp_service(const groot::setting& config,
                             task_router *router,
                             const work_service_delegate *service_delegate) noexcept;
        virtual ~tcp_service();

        void setup() noexcept final;
        void reset() noexcept final;

        void shutdown(tcp_connection *connection) noexcept;

    private:
        uv_loop_t *                             _loop;
        tcp_connection_manager::uptr            _connections;

        void listen(const groot::endpoint::sptr& endpoint, u16 backlog, u32 keepalive) noexcept;
        void connect(const groot::endpoint::sptr& endpoint) noexcept;

        void setup_sockaddr(const groot::endpoint::sptr& endpoint, groot::socket_address *addr) noexcept;

        void setup_servers() noexcept;
        void setup_clients() noexcept;

        void on_connection(groot::network_handle *handle, int status) noexcept;
        void on_connect(uv_connect_t *request, int status) noexcept;
        void on_alloc(groot::network_handle *handle, size_t suggested_size, uv_buf_t *buffer) noexcept;
        void on_read(groot::network_handle *handle, ssize_t nread, const uv_buf_t *buffer) noexcept;
        void on_write(uv_write_t *request, int status) noexcept;
        void on_shutdown(uv_shutdown_t *request, int status) noexcept;

        static void connection_routine(uv_stream_t *stream, int status) noexcept;
        static void connect_routine(uv_connect_t *request, int status) noexcept;
        static void alloc_routine(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buffer) noexcept;
        static void read_routine(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buffer) noexcept;
        static void write_routine(uv_write_t *request, int status) noexcept;
        static void shutdown_routine(uv_shutdown_t *request, int status) noexcept;

    };

}

#endif /* ROCKET_TCP_SERVICE_H */
