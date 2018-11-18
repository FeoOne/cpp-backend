/**
 * @file bitcoin_rpc_service.h
 * @author Feo
 * @date 12/11/2018
 * @brief
 */

#ifndef BACKEND_BITCOIN_RPC_SERVICE_H
#define BACKEND_BITCOIN_RPC_SERVICE_H

#include <curl/curl.h>

#include <engine.h>

#define BITCOIN_RPC_SERVICE     delegate()->service<bitcoin_rpc_service>()

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
        s64 get_estimated_fee(size_t wait_for_block_count) noexcept;

    private:
        const char *        _bitcoin_rpc_address;
        const char *        _bitcoin_rpc_credentials;

        bool perform(const Json::Value& in, Json::Value& out) noexcept;

        static size_t write_callback(void *ptr, size_t size, size_t nmemb, std::string* data) noexcept;

    };

}

#endif /* BACKEND_BITCOIN_RPC_SERVICE_H */
