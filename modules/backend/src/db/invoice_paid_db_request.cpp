/**
 * @file invoice_paid_db_request.cpp
 * @author Feo
 * @date 2018-12-20
 * @brief
 */

#include "db/invoice_paid_db_request.h"

namespace backend {

    static const char *sql { "SELECT invoice_paid($1::UUID, $2::VARCHAR);" };
    static constexpr size_t param_count { 2 };

    invoice_paid_db_request::invoice_paid_db_request(const stl::uuid& invoice_guid, const std::string& txid) noexcept :
            engine::db_request(sql, param_count)
    {
        _params << invoice_guid;
        _params << txid;
    }

    // virtual
    invoice_paid_db_request::~invoice_paid_db_request()
    {
    }

    // virtual
    void invoice_paid_db_request::process_response(engine::db_response *) noexcept
    {
        _is_success = true;
    }

}
