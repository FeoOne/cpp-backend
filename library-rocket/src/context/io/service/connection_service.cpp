/**
 * @file assembly_service.cpp
 * @author Feo
 * @date 28/09/2018
 * @brief
 */

#include "context/io/io_loop.h"
#include "context/io/service/tcp_service.h"
#include "context/io/service/udp_service.h"

#include "context/io/service/connection_service.h"

namespace rocket {

    connection_service::connection_service(const groot::setting& config,
                                       task_router *router,
                                       const work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _tcp_connections { tcp_connection_manager::make_unique() },
            _udp_connections { udp_connection_manager::make_unique() }
    {
    }

    // virtual
    void connection_service::setup() noexcept
    {
        setup_masters();
        setup_slaves();
    }

    // virtual
    void connection_service::reset() noexcept
    {

    }

    void connection_service::setup_masters() noexcept
    {
        auto servers_config { config()[consts::config::key::MASTER] };
        if (servers_config.is_null()) {
            lognotice("No masters presented.");
            return;
        }

        const std::unordered_map<std::string_view, std::function<void(const groot::setting&)>> setup {
            // setup tcp master connection
            { consts::config::io::TCP, [this](const groot::setting& config) {
                auto name { config[consts::config::key::NAME].to_string() };
                auto listen { config[consts::config::key::LISTEN].to_string() };
                auto port { config[consts::config::key::PORT].to_int32<u16>() };
                auto backlog { config[consts::config::key::BACKLOG].to_int32<u16>() };
                auto keepalive { config[consts::config::key::KEEPALIVE].to_int32<u16>() };

                auto connection { _tcp_connections->produce() };
                connection->setup(name, listen, port, backlog, keepalive);

                delegate()->service<tcp_service>()->register_local_connection(connection);
            } },
            // setup udp master connection
            { consts::config::io::UDP, [this](const groot::setting& config) {} },
        };

        for (size_t i = 0; i < servers_config.size(); ++i) {
            auto server_config { servers_config[i] };
            setup.at(server_config[consts::config::key::TYPE].to_string())(server_config);
        }
    }

    void connection_service::setup_slaves() noexcept
    {
        auto clients_config { config()[consts::config::key::SLAVE] };
        if (clients_config.is_null()) {
            lognotice("No slaves presented.");
            return;
        }

        const std::unordered_map<std::string_view, std::function<void(const groot::setting&)>> setup {
            // setup tcp slave connection
            { consts::config::io::TCP, [this](const groot::setting& config) {
                auto name { config[consts::config::key::NAME].to_string() };
                auto host { config[consts::config::key::HOST].to_string() };
                auto port { config[consts::config::key::PORT].to_int32<u16>() };

                auto connection { _tcp_connections->produce() };
                connection->setup(name, host, port);

                delegate()->service<tcp_service>()->register_local_connection(connection);
            } },
            // setup udp slave connection
            { consts::config::io::UDP, [this](const groot::setting& config) {} },
        };

        for (size_t i = 0; i < clients_config.size(); ++i) {
            auto client_config { clients_config[i] };
            setup.at(client_config[consts::config::key::TYPE].to_string())(client_config);
        }
    }

}
