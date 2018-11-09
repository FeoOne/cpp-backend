/**
 * @file db_request.cpp
 * @author Feo
 * @date 14/09/2018
 * @brief
 */

#include "context/db/core/db_request.h"

namespace engine {

    db_request::db_request(const std::string_view& query, size_t param_count) noexcept :
            _params { param_count },
            _query { query },
            _connection { nullptr },
            _callback { nullptr }
    {
    }

    db_request::~db_request()
    {
    }

    void db_request::assign_callback(callback&& fn) noexcept
    {
        _callback = std::move(fn);
    }

    void db_request::assign_connection(db_connection *connection) noexcept
    {
        _connection = connection;
    }

}
