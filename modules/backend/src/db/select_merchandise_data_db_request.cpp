/**
 * @file select_merchandise_data_db_request.cpp
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#include "select_merchandise_data_db_request.h"

namespace backend {

    static constexpr std::string_view sql { "SELECT * FROM select_merchandise_data($1::UUID);" };
    static constexpr size_t param_count { 1 };

    select_merchandise_data_db_request::select_merchandise_data_db_request(const stl::uuid& guid) noexcept :
            engine::db_request(sql, param_count)
    {
//        auto guid_string { guid.to_string() };
//        _params << guid_string;
        _params << guid;
        _params.bake();
    }

    void select_merchandise_data_db_request::process_response(engine::db_response *response) noexcept
    {
        auto row_count { response->row_count() };
        if (row_count != 1) {
            logwarn("Failed to process 'select_merchandise_data_db_request'.");
            return;
        }

        static size_t merchandise_id_column_index { response->column_index("merchandise_id") };
        static size_t merchandise_guid_column_index { response->column_index("merchandise_guid") };
        static size_t merchandise_label_column_index { response->column_index("merchandise_label") };
        static size_t merchant_id_column_index { response->column_index("merchant_id") };
        static size_t merchant_guid_column_index { response->column_index("merchant_guid") };
        static size_t merchant_label_column_index { response->column_index("merchant_label") };
        static size_t user_id_column_index { response->column_index("user_id") };
        static size_t callback_url_column_index { response->column_index("callback_url") };
        static size_t private_key_column_index { response->column_index("private_key") };

        response->value(0, merchandise_id_column_index, &merchandise_id);
        response->value(0, merchandise_guid_column_index, merchandise_guid);
        response->value(0, merchandise_label_column_index, &merchandise_label);
        response->value(0, merchant_id_column_index, &merchant_id);
        response->value(0, merchant_guid_column_index, merchant_guid);
        response->value(0, merchant_label_column_index, &merchant_label);
        response->value(0, user_id_column_index, &user_id);
        response->value(0, callback_url_column_index, &callback_url);
        response->value(0, private_key_column_index, &private_key);

        _is_success = true;
    }

}
