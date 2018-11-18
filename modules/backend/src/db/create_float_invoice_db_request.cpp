/**
 * @file select_merchandise_data_db_request.cpp
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#include "create_float_invoice_db_request.h"

namespace backend {

    static const char *sql { "SELECT * FROM create_float_invoice($1::UUID, $2::VARCHAR, $3::BIGINT, $4::BIGINT);" };
    static constexpr size_t param_count { 4 };

    create_float_invoice_db_request::create_float_invoice_db_request(const stl::uuid& pending_guid,
                                                                     const stl::uuid& merchandise_guid,
                                                                     const std::string& mail,
                                                                     s64 amount,
                                                                     s64 fee) noexcept :
            engine::db_request(sql, param_count),
            invoice_id { 0 },
            wallet_guid {},
            confirm_block_count { 0 },
            callback_url { nullptr },
            created_at { 0 },
            _pending_guid { pending_guid }
    {
        _params << merchandise_guid;
        _params << mail;
        _params << amount;
        _params << fee;
    }

    // virtual
    create_float_invoice_db_request::~create_float_invoice_db_request()
    {
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
        static size_t created_at_column_index { response->column_index("created_at") };

        response->value(0, invoice_id_column_index, &invoice_id);
        response->value(0, invoice_guid_column_index, invoice_guid);
        response->value(0, wallet_guid_column_index, wallet_guid);
        response->value(0, confirm_block_count_column_index, &confirm_block_count);
        response->value(0, callback_url_column_index, &callback_url);
        response->value(0, created_at_column_index, &created_at);

        _is_success = true;
    }

}
