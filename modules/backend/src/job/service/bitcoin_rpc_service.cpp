/**
 * @file bitcoin_rpc_service.cpp
 * @author Feo
 * @date 12/11/2018
 * @brief
 */

#include "main/backend_consts.h"

#include "job/service/bitcoin_rpc_service.h"

namespace backend {

    bitcoin_rpc_service::bitcoin_rpc_service(const stl::setting& config,
                                             engine::task_router *router,
                                             const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {

    }

    // virtual
    bitcoin_rpc_service::~bitcoin_rpc_service()
    {
    }

    void bitcoin_rpc_service::setup() noexcept
    {
        if (!config().lookup_string(consts::config::key::bitcoin_rpc_address, &_bitcoin_rpc_address)) {
            logemerg("Can't setup db connection service: no '%s' presented.", consts::config::key::bitcoin_rpc_address);
        }
    }

    void bitcoin_rpc_service::reset() noexcept
    {

    }

    size_t bitcoin_rpc_service::get_block_count() noexcept
    {

    }

}
