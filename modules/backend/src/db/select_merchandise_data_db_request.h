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

        explicit select_merchandise_data_db_request(const stl::uuid& guid) noexcept;
        virtual ~select_merchandise_data_db_request() = default;

    private:

    };

}

#endif /* BACKEND_SELECT_MERCHANDISE_DATA_DB_REQUEST_H */
