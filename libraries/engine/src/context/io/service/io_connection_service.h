/**
 * @file connection_service.h
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#ifndef ENGINE_ASSEMBLY_SERVICE_H
#define ENGINE_ASSEMBLY_SERVICE_H

#include "work/work_service.h"
#include "context/io/connection/connection_manager.h"

namespace engine {

    /**
     * Configurator.
     */
    class io_connection_service final : public stl::crucial<work_service, io_connection_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(io_connection_service)
        STL_DELETE_ALL_DEFAULT(io_connection_service)

        explicit io_connection_service(const stl::setting& config,
                                    task_router *router,
                                    const work_service_delegate *delegate) noexcept;

        virtual ~io_connection_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

        template<typename T>
        connection_manager<T> *manager() noexcept;

    private:
        tcp_connection_manager::uptr        _tcp_connections;
        udp_connection_manager::uptr        _udp_connections;

        void setup_masters() noexcept;
        void setup_slaves() noexcept;

        void handle_disconnect_connection_task(engine::basic_task *base_task) noexcept;

    };

    template<>
    tcp_connection_manager *io_connection_service::manager<tcp_connection>() noexcept;

    template<>
    udp_connection_manager *io_connection_service::manager<udp_connection>() noexcept;

}

#endif /* ENGINE_ASSEMBLY_SERVICE_H */
