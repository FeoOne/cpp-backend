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
        _params << guid;
        _params.bake();
    }

}
