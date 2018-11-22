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

        explicit bitcoin_rpc_service(const stl::setting& config,
                                     engine::task_router *router,
                                     const engine::work_service_delegate *delegate) noexcept;

        virtual ~bitcoin_rpc_service();

        void setup() noexcept final;
        void reset() noexcept final;

        size_t get_block_count() noexcept;
        s64 get_estimated_fee(size_t wait_for_block_count) noexcept;
        bool get_raw_mempool(bool is_verbose, Json::Value& out) noexcept;
        bool get_raw_transaction(const char *txid, Json::Value& out) noexcept;

    private:
        struct curl_context {
            engine::poll_handle     poll_handle;
            curl_socket_t           socket;
        };

        const char *                                                _bitcoin_rpc_address;
        const char *                                                _bitcoin_rpc_credentials;

        engine::timer_handle                                        _timeout_timer_handle;
        CURLM *                                                     _curl;

        std::unordered_map<CURL *, curl_context *>                  _context_by_curl;
        std::unordered_map<engine::poll_handle *, curl_context *>   _context_by_poll;

        void init_in_json(Json::Value& in, const std::string& method) noexcept;

        void check_multi_info() noexcept;

        int on_handle_socket(CURL *easy, curl_socket_t socket, int action, void *userp) noexcept;
        int on_start_timeout(CURLM *multi, long timeout_ms, void *userp) noexcept;
        void on_curl_perform(engine::poll_handle *poll_handle, int status, int events) noexcept;
        void on_curl_close(engine::poll_handle *poll_handle) noexcept;

        static int handle_socket_fn(CURL *easy, curl_socket_t socket, int action, void *userp, void *socketp) noexcept;
        static int start_timeout_fn(CURLM *multi, long timeout_ms, void *userp) noexcept;
        static void curl_perform_fn(uv_poll_t *poll_handle, int status, int events) noexcept;
        static void curl_close_fn(uv_handle_t *poll_handle) noexcept;




        bool perform(const Json::Value& in, Json::Value& out) noexcept;

        static size_t write_callback(void *ptr, size_t size, size_t nmemb, std::string* data) noexcept;

    };

}

#endif /* BACKEND_BITCOIN_RPC_SERVICE_H */
