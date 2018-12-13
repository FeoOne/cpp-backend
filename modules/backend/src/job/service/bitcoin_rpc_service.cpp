/**
 * @file bitcoin_rpc_service.cpp
 * @author Feo
 * @date 12/11/2018
 * @brief
 */

#include "bitcoin/bitcoin.h"
#include "main/backend_consts.h"

#include "job/service/bitcoin_rpc_service.h"

namespace backend {

    bitcoin_rpc_service::bitcoin_rpc_service(const stl::setting& config,
                                             engine::task_router *router,
                                             const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _bitcoin_rpc_address { nullptr },
            _bitcoin_rpc_credentials { nullptr }
    {
    }

    // virtual
    bitcoin_rpc_service::~bitcoin_rpc_service()
    {
    }

    // virtual
    void bitcoin_rpc_service::setup() noexcept
    {
        configure();
    }

    // virtual
    void bitcoin_rpc_service::reset() noexcept
    {

    }

    void bitcoin_rpc_service::configure() noexcept
    {
        if (!config().lookup_string(consts::config::key::bitcoin_rpc_address, &_bitcoin_rpc_address)) {
            logemerg("Can't setup db connection service: no '%s' presented.",
                     consts::config::key::bitcoin_rpc_address);
        }

        if (!config().lookup_string(consts::config::key::bitcoin_rpc_credentials, &_bitcoin_rpc_credentials)) {
            logemerg("Can't setup db connection service: no '%s' presented.",
                     consts::config::key::bitcoin_rpc_credentials);
        }
    }

    void bitcoin_rpc_service::perform(Json::Value& json, std::function<void(Json::Value&)>&& callback) noexcept
    {
        auto request { new (std::nothrow) engine::http_client_request(SOUP_METHOD_POST, "") };
        auto task { new (std::nothrow) engine::http_client_request_task(request,
                                                                        [](engine::http_server_response *response) {
                                                                            //
                                                                        }) };

        router()->enqueue(task);
    }

//    void bitcoin_rpc_service::setup() noexcept
//    {
//        if (!config().lookup_string(consts::config::key::bitcoin_rpc_address, &_bitcoin_rpc_address)) {
//            logemerg("Can't setup db connection service: no '%s' presented.",
//                     consts::config::key::bitcoin_rpc_address);
//        }
//
//        if (!config().lookup_string(consts::config::key::bitcoin_rpc_credentials, &_bitcoin_rpc_credentials)) {
//            logemerg("Can't setup db connection service: no '%s' presented.",
//                     consts::config::key::bitcoin_rpc_credentials);
//        }
//
//        if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
//            logerror("Failed to init libcurl.");
//        }
//
//        uv_timer_init(delegate()->loop<engine::job_loop>()->loop(), &_timeout_timer_handle.timer);
//
//        _curl = curl_multi_init();
//        curl_multi_setopt(_curl, CURLMOPT_SOCKETFUNCTION, &bitcoin_rpc_service::handle_socket_fn);
//        curl_multi_setopt(_curl, CURLMOPT_TIMERFUNCTION, &bitcoin_rpc_service::start_timeout_fn);
//    }
//
//    void bitcoin_rpc_service::reset() noexcept
//    {
//        curl_multi_cleanup(_curl);
//        _curl = nullptr;
//    }
//
//    size_t bitcoin_rpc_service::get_block_count() noexcept
//    {
//        Json::Value in;
//        init_in_json(in, "getblockcount");
//
//        Json::Value out;
//        size_t result { 0 };
//
//        if (perform(in, out)) {
//            result = out["result"].asUInt();
//        }
//
//        return result;
//    }
//
//    s64 bitcoin_rpc_service::get_estimated_fee(size_t wait_for_block_count) noexcept
//    {
//        logassert(wait_for_block_count >= 2 && wait_for_block_count <= 1000, "conf_target out of bounds.");
//
//        Json::Value in;
//        init_in_json(in, "estimatesmartfee");
//        in["params"] = Json::Value { Json::arrayValue };
//        in["params"].append(static_cast<u32>(wait_for_block_count));
//        in["params"].append("ECONOMICAL"); // todo: add configuration for "UNSET" "ECONOMICAL" "CONSERVATIVE"
//
//        Json::Value out;
//        s64 result { 0 };
//
//        if (perform(in, out)) {
//            result = bitcoin::json_value_to_amount(out["result"]["feerate"].asDouble());
//        }
//
//        return result;
//    }
//
//    bool bitcoin_rpc_service::get_raw_mempool(bool is_verbose, Json::Value& out) noexcept
//    {
//        Json::Value in;
//        init_in_json(in, "getrawmempool");
//        in["params"] = Json::Value { Json::arrayValue };
//        in["params"].append(is_verbose);
//
//        return perform(in, out);
//    }
//
//    bool bitcoin_rpc_service::get_raw_transaction(const char *txid, Json::Value& out) noexcept
//    {
//        Json::Value in;
//        init_in_json(in, "getrawtransaction");
//        in["params"] = Json::Value { Json::arrayValue };
//        in["params"].append(txid);
//        in["params"].append(true);
//
//        return perform(in, out);
//    }
//
//    void bitcoin_rpc_service::init_in_json(Json::Value& in, const std::string& method) noexcept
//    {
//        in["jsonrpc"] = "1.0";
//        in["method"] = method;
//    }
//
//    bool bitcoin_rpc_service::perform(const Json::Value& in, Json::Value& out) noexcept
//    {
//        static const curl_slist *headers { curl_slist_append(nullptr, "content-type: text/plain;") };
//
//        Json::StreamWriterBuilder write_builder;
//        auto data { Json::writeString(write_builder, in) };
//
//        CURL *curl { curl_easy_init() };
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        curl_easy_setopt(curl, CURLOPT_URL, _bitcoin_rpc_address);
//        curl_easy_setopt(curl, CURLOPT_USERPWD, _bitcoin_rpc_credentials);
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.data());
//        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);
//
//        std::string response;
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, bitcoin_rpc_service::write_callback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//
//        {
//            auto result { curl_easy_perform(curl) };
//            if (result != CURLE_OK) {
//                return false;
//            }
//        }
//
//        curl_easy_cleanup(curl);
//
//        Json::CharReaderBuilder read_builder;
//        auto reader { read_builder.newCharReader() };
//        std::string errors;
//        bool result { reader->parse(response.data(), response.data() + response.length(), &out, &errors) };
//        logassert(result, "Failed to parse json: %s", errors.data());
//        logassert(out["error"].isNull(), "Failed to process request: %s", out["error"]["message"].asCString());
//        delete reader;
//
//        return result && out["error"].isNull();
//    }
//
//    void bitcoin_rpc_service::check_multi_info() noexcept
//    {
//        int pending { 0 };
//        CURLMsg *message { nullptr };
//
//        while ((message = curl_multi_info_read(message, &pending)) != nullptr) {
//            switch (message->msg) {
//                case CURLMSG_DONE: {
//                    /**
//                     * Do not use message data after calling curl_multi_remove_handle() and
//                     * curl_easy_cleanup(). As per curl_multi_info_read() docs:
//                     * "WARNING: The data the returned pointer points to will not survive
//                     * calling curl_multi_cleanup, curl_multi_remove_handle or
//                     * curl_easy_cleanup."
//                     */
//                    auto easy { message->easy_handle };
//
//                    break;
//                }
//            }
//        }
//    }
//
//    int bitcoin_rpc_service::on_handle_socket(CURL *easy, curl_socket_t socket, int action, void *userp) noexcept
//    {
//        switch(action) {
//            case CURL_POLL_IN:
//            case CURL_POLL_OUT:
//            case CURL_POLL_INOUT: {
//                curl_multi_assign(_curl, socket, this);
//
//                int events = 0;
//                if (action != CURL_POLL_IN) {
//                    events |= UV_WRITABLE;
//                }
//                if (action != CURL_POLL_OUT) {
//                    events |= UV_READABLE;
//                }
//
//                curl_context *context { nullptr };
//                auto it { _context_by_curl.find(easy) };
//                if (it == _context_by_curl.end()) {
//                    context = new curl_context;
//                    context->socket = socket;
//
//                    uv_poll_init_socket(delegate()->loop<engine::job_loop>()->loop(),
//                                        &context->poll_handle.poll,
//                                        socket);
//                    uv_handle_set_data(&context->poll_handle.handle, this);
//
//                    _context_by_curl[easy] = context;
//                    _context_by_poll[&context->poll_handle] = context;
//                }
//
//                uv_poll_start(&context->poll_handle.poll, events, &bitcoin_rpc_service::curl_perform_fn);
//                break;
//            }
//            case CURL_POLL_REMOVE: {
//                auto it { _context_by_curl.find(easy) };
//                if (it != _context_by_curl.end()) {
//                    auto context { it->second };
//
//                    uv_poll_stop(&context->poll_handle.poll);
//                    uv_close(&context->poll_handle.handle, &bitcoin_rpc_service::curl_close_fn);
//                    curl_multi_assign(_curl, socket, nullptr);
//
//                    _context_by_curl.erase(it);
//                }
//                break;
//            }
//            default: {
//            }
//        }
//
//        return 0;
//    }
//
//    int bitcoin_rpc_service::on_start_timeout(CURLM *multi, long timeout_ms, void *userp) noexcept
//    {
//
//    }
//
//    void bitcoin_rpc_service::on_curl_perform(engine::poll_handle *poll_handle, int status, int events) noexcept
//    {
//        auto it { _context_by_poll.find(poll_handle) };
//        if (it == _context_by_poll.end()) {
//            logwarn("Curl perform error.");
//            return;
//        }
//
//        auto context { it->second };
//
//        int running_handles;
//        int flags = 0;
//
//        if (events & UV_READABLE) {
//            flags |= CURL_CSELECT_IN;
//        }
//        if (events & UV_WRITABLE) {
//            flags |= CURL_CSELECT_OUT;
//        }
//
//        curl_multi_socket_action(_curl, context->socket, flags, &running_handles);
//
//        check_multi_info();
//    }
//
//    void bitcoin_rpc_service::on_curl_close(engine::poll_handle *poll_handle) noexcept
//    {
//        auto it { _context_by_poll.find(poll_handle) };
//        if (it != _context_by_poll.end()) {
//            auto context { it->second };
//            delete context;
//            _context_by_poll.erase(it);
//        }
//    }
//
//    // static
//    int bitcoin_rpc_service::handle_socket_fn(CURL *easy,
//                                              curl_socket_t socket,
//                                              int action,
//                                              void *userp,
//                                              void *socketp) noexcept
//    {
//        int result { 0 };
//        if (socketp != nullptr) {
//            result = reinterpret_cast<bitcoin_rpc_service *>(socketp)->on_handle_socket(easy, socket, action, userp);
//        }
//        return result;
//    }
//
//    // static
//    int bitcoin_rpc_service::start_timeout_fn(CURLM *multi, long timeout_ms, void *userp) noexcept
//    {
//
//    }
//
//    // static
//    void bitcoin_rpc_service::curl_perform_fn(uv_poll_t *poll_handle, int status, int events) noexcept
//    {
//        if (poll_handle != nullptr && poll_handle->data != nullptr) {
//            auto handle { reinterpret_cast<engine::poll_handle *>(poll_handle) };
//            reinterpret_cast<bitcoin_rpc_service *>(poll_handle->data)->on_curl_perform(handle, status, events);
//        }
//    }
//
//    // static
//    void bitcoin_rpc_service::curl_close_fn(uv_handle_t *poll_handle) noexcept
//    {
//        if (poll_handle != nullptr && poll_handle->data != nullptr) {
//            auto handle { reinterpret_cast<engine::poll_handle *>(poll_handle) };
//            reinterpret_cast<bitcoin_rpc_service *>(poll_handle->data)->on_curl_close(handle);
//        }
//    }
//
//    // static
//    size_t bitcoin_rpc_service::write_callback(void *ptr, size_t size, size_t nmemb, std::string* data) noexcept
//    {
//        data->append(reinterpret_cast<char *>(ptr), size * nmemb);
//        return size * nmemb;
//    }

}
