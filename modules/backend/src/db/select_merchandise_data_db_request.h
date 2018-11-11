/**
 * @file select_merchandise_data_db_request.h
 * @author Feo
 * @date 08/11/2018
 * @brief
 */

#ifndef BACKEND_SELECT_MERCHANDISE_DATA_DB_REQUEST_H
#define BACKEND_SELECT_MERCHANDISE_DATA_DB_REQUEST_H

#include <engine.h>

namespace backend {

    class select_merchandise_data_db_request : public engine::db_request {
    public:
        STL_DELETE_ALL_DEFAULT(select_merchandise_data_db_request)

        u64             merchandise_id;
        stl::uuid       merchandise_guid;
        char *          merchandise_label;
        u64             merchant_id;
        stl::uuid       merchant_guid;
        char *          merchant_label;
        u64             user_id;
        char *          callback_url;
        char *          private_key;

        explicit select_merchandise_data_db_request(const stl::uuid& guid, const stl::uuid& invoice_guid) noexcept;
        virtual ~select_merchandise_data_db_request() = default;

        void process_response(engine::db_response *response) noexcept final;

        const stl::uuid& invoice_guid() const noexcept { return _invoice_guid; }

    private:

        stl::uuid       _invoice_guid;

    };

}

#endif /* BACKEND_SELECT_MERCHANDISE_DATA_DB_REQUEST_H */
