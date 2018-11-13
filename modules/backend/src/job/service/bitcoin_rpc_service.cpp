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
            crucial(config, router, delegate),
            _bitcoin_rpc_address { nullptr },
            _bitcoin_rpc_credentials { nullptr }
    {

    }

    // virtual
    bitcoin_rpc_service::~bitcoin_rpc_service()
    {
    }

    void bitcoin_rpc_service::setup() noexcept
    {
        if (!config().lookup_string(consts::config::key::bitcoin_rpc_address, &_bitcoin_rpc_address)) {
            logemerg("Can't setup db connection service: no '%s' presented.",
                     consts::config::key::bitcoin_rpc_address);
        }

        if (!config().lookup_string(consts::config::key::bitcoin_rpc_credentials, &_bitcoin_rpc_credentials)) {
            logemerg("Can't setup db connection service: no '%s' presented.",
                     consts::config::key::bitcoin_rpc_credentials);
        }

        get_block_count();
    }

    void bitcoin_rpc_service::reset() noexcept
    {

    }

    size_t bitcoin_rpc_service::get_block_count() noexcept
    {
        Json::Value in;
        in["id"] = "curltest";
        in["method"] = "getrawmempool";
        in["verbose"] = true;
//        in["method"] = "getrawtransaction";
//        in["txid"] = "a37392db002769d1f7248b150b4ee11f23d0eb74ab4fa564b02fd9cc9be8e447";

        Json::Value out;

        perform(in, out);
    }

    size_t bitcoin_rpc_service::perform(const Json::Value& in, Json::Value& out) noexcept
    {
        static const curl_slist *headers { curl_slist_append(nullptr, "content-type: text/plain;") };

        Json::StreamWriterBuilder write_builder;
        auto data { Json::writeString(write_builder, in) };

        CURL *curl { curl_easy_init() };
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, _bitcoin_rpc_address);
        curl_easy_setopt(curl, CURLOPT_USERPWD, _bitcoin_rpc_credentials);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.data());
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, bitcoin_rpc_service::write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        auto result { curl_easy_perform(curl) };

        printf("%s", response_string.data());

        curl_easy_cleanup(curl);

        Json::CharReaderBuilder read_builder;
        auto reader { read_builder.newCharReader() };
        std::string errors;
        bool status { reader->parse(response_string.data(),
                                    response_string.data() + response_string.length(),
                                    &out,
                                    &errors) };
        delete reader;

        return 0;
    }

    // static
    size_t bitcoin_rpc_service::write_callback(void *ptr, size_t size, size_t nmemb, std::string* data) noexcept
    {
        data->append(reinterpret_cast<char *>(ptr), size * nmemb);
        return size * nmemb;
    }

}
