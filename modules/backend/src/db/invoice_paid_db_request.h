/**
 * @file invoice_paid_db_request.h
 * @author Feo
 * @date 2018-12-20
 * @brief
 */

#ifndef BACKEND_INVOICE_PAID_DB_REQUEST_H
#define BACKEND_INVOICE_PAID_DB_REQUEST_H

#include <engine.h>

namespace backend {

    class invoice_paid_db_request final : public engine::db_request {
    public:
        STL_DELETE_ALL_DEFAULT(invoice_paid_db_request)

        explicit invoice_paid_db_request(const stl::uuid& invoice_guid, const std::string& txid) noexcept;
        virtual ~invoice_paid_db_request();

        void process_response(engine::db_response *response) noexcept final;

    private:

    };

}

#endif /* BACKEND_INVOICE_PAID_DB_REQUEST_H */
