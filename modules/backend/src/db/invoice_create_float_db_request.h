/**
 * @file invoice_create_float_db_request.h
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#ifndef BACKEND_INVOICE_CREATE_FLOAT_DB_REQUEST_H
#define BACKEND_INVOICE_CREATE_FLOAT_DB_REQUEST_H

#include <engine.h>

namespace backend {

    class invoice_create_float_db_request final : public engine::db_request {
    public:
        STL_DELETE_ALL_DEFAULT(invoice_create_float_db_request)

        u64                 invoice_id;
        stl::uuid           invoice_guid;
        stl::uuid           wallet_guid;
        u32                 confirm_block_count;
        char *              callback_url;
        u64                 created_at;

        explicit invoice_create_float_db_request(const stl::uuid& pending_guid,
                                                 const stl::uuid& merchandise_guid,
                                                 const std::string& mail,
                                                 s64 amount,
                                                 s64 fee) noexcept;
        virtual ~invoice_create_float_db_request();

        void process_response(engine::db_response *response) noexcept final;

        const stl::uuid& pending_guid() const noexcept { return _pending_guid; }

    private:
        stl::uuid           _pending_guid;

    };

}

#endif /* BACKEND_INVOICE_CREATE_FLOAT_DB_REQUEST_H */
