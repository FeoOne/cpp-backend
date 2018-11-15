/**
 * @file select_merchandise_data_db_request.cpp
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#include "create_float_invoice_db_request.h"

namespace backend {

    static const char *sql { "SELECT * FROM create_float_invoice($1::UUID, $2::VARCHAR, $3::BIGINT);" };
    static constexpr size_t param_count { 3 };

    create_float_invoice_db_request::create_float_invoice_db_request(const stl::uuid& merchandise_guid,
                                                                     const char *mail,
                                                                     u64 amount) noexcept :
            engine::db_request(sql, param_count),
            merchandise_guid { merchandise_guid },
            invoice_id { 0 },
            wallet_guid {},
            confirm_block_count { 0 },
            callback_url { nullptr }
    {
        _params << merchandise_guid;
        _params << mail;
        _params << amount;

        _params.bake();
    }

    // virtual
    create_float_invoice_db_request::~create_float_invoice_db_request()
    {
        // memory freed in `pending_invoice::~pending_invoice()`
//        if (callback_url != nullptr) {
//            std::free(callback_url);
//        }
    }

    // virtual
    void create_float_invoice_db_request::process_response(engine::db_response *response) noexcept
    {
        auto row_count { response->row_count() };
        if (row_count != 1) {
            logwarn("Failed to process 'create_float_invoice'.");
            return;
        }

        static size_t invoice_id_column_index { response->column_index("invoice_id") };
        static size_t invoice_guid_column_index { response->column_index("invoice_guid") };
        static size_t wallet_guid_column_index { response->column_index("wallet_guid") };
        static size_t confirm_block_count_column_index { response->column_index("confirm_block_count") };
        static size_t callback_url_column_index { response->column_index("callback_url") };

        response->value(0, invoice_id_column_index, &invoice_id);
        response->value(0, invoice_guid_column_index, invoice_guid);
        response->value(0, wallet_guid_column_index, wallet_guid);
        response->value(0, confirm_block_count_column_index, &confirm_block_count);
        response->value(0, callback_url_column_index, &callback_url);

        callback_url = strdup(callback_url);

        _is_success = true;
    }

}
