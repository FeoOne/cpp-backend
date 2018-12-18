/**
 * @file bitcoin_rpc_service.h
 * @author Feo
 * @date 12/11/2018
 * @brief
 * @see https://curl.haxx.se/libcurl/c/multi-uv.html
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

        using handler = std::function<void(const Json::Value&)>;

        explicit bitcoin_rpc_service(const stl::setting& config,
                                     engine::task_router *router,
                                     const engine::work_service_delegate *delegate) noexcept;

        virtual ~bitcoin_rpc_service();

        void setup() noexcept final;
        void reset() noexcept final;

        void get_estimated_fee(size_t wait_block_count, handler&& callback) noexcept;
        bool get_raw_mempool(bool is_verbose, handler&& callback) noexcept;
        bool get_raw_transaction(const char *txid, handler&& callback) noexcept;

    private:
        const char *                                                _bitcoin_rpc_address;
        const char *                                                _bitcoin_rpc_credentials;

        size_t                                                      _request_counter;
        stl::ring_buffer<std::function<void(Json::Value&)>, 64>     _request_handlers;

        Json::StreamWriterBuilder                                   _json_writer_builder;

        void configure() noexcept;

        void perform(Json::Value& json) noexcept;
        void on_perform(engine::http_client_response *response) noexcept;

        u64 init_in_json(Json::Value& in, const std::string& method) noexcept;

    };

}

#endif /* BACKEND_BITCOIN_RPC_SERVICE_H */
