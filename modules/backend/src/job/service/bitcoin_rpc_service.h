/**
 * @file bitcoin_rpc_service.h
 * @author Feo
 * @date 12/11/2018
 * @brief
 */

#ifndef BACKEND_BITCOIN_RPC_SERVICE_H
#define BACKEND_BITCOIN_RPC_SERVICE_H

#include <engine.h>

namespace backend {

    class bitcoin_rpc_service : public stl::crucial<engine::work_service, bitcoin_rpc_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(bitcoin_rpc_service)
        STL_DELETE_ALL_DEFAULT(bitcoin_rpc_service)

        explicit bitcoin_rpc_service(const stl::setting& config,
                                     engine::task_router *router,
                                     const engine::work_service_delegate *delegate) noexcept;

        virtual ~bitcoin_rpc_service();

        void setup() noexcept final;
        void reset() noexcept final;

        size_t get_block_count() noexcept;

    private:
        const char *        _bitcoin_rpc_address;

    };

}

#endif /* BACKEND_BITCOIN_RPC_SERVICE_H */
