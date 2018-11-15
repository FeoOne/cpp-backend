/**
 * @file select_merchandise_data_db_request.h
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#ifndef BACKEND_CREATE_FLOAT_INVOICE_DB_REQUEST_H
#define BACKEND_CREATE_FLOAT_INVOICE_DB_REQUEST_H

#include <engine.h>

namespace backend {

    class create_float_invoice_db_request final : public engine::db_request {
    public:
        STL_DELETE_ALL_DEFAULT(create_float_invoice_db_request)

        const stl::uuid     merchandise_guid;

        u64                 invoice_id;
        stl::uuid           invoice_guid;
        stl::uuid           wallet_guid;
        u32                 confirm_block_count;
        char *              callback_url;

        explicit create_float_invoice_db_request(const stl::uuid& merchandise_guid,
                                                 const char *mail,
                                                 u64 amount) noexcept;
        virtual ~create_float_invoice_db_request();

        void process_response(engine::db_response *response) noexcept final;

    private:

    };

}

#endif /* BACKEND_CREATE_FLOAT_INVOICE_DB_REQUEST_H */
