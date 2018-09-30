/**
 * @file connection_service.h
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#ifndef ROCKET_ASSEMBLY_SERVICE_H
#define ROCKET_ASSEMBLY_SERVICE_H

#include "work/work_service.h"
#include "context/io/connection/connection_manager.h"

namespace rocket {

    /**
     * Configurator.
     */
    class connection_service final : public groot::crucial<work_service, connection_service> {
    public:
        GR_DECLARE_SMARTPOINTERS(connection_service)
        GR_DELETE_ALL_DEFAULT(connection_service)

        explicit connection_service(const groot::setting& config,
                                    task_router *router,
                                    const work_service_delegate *delegate) noexcept;

        virtual ~connection_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

        template<typename T>
        connection_manager<T> *manager() noexcept;

    private:
        tcp_connection_manager::uptr        _tcp_connections;
        udp_connection_manager::uptr        _udp_connections;

        void setup_masters() noexcept;
        void setup_slaves() noexcept;

    };

    template<>
    tcp_connection_manager *connection_service::manager<tcp_connection>() noexcept {
        return _tcp_connections.get();
    }

    template<>
    udp_connection_manager *connection_service::manager<udp_connection>() noexcept {
        return _udp_connections.get();
    }

}

#endif /* ROCKET_ASSEMBLY_SERVICE_H */
