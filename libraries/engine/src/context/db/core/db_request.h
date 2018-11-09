/**
 * @file db_request.h
 * @author Feo
 * @date 14/09/2018
 * @brief
 */

#ifndef ENGINE_DB_REQUEST_H
#define ENGINE_DB_REQUEST_H

#include <stl.h>

#include "context/db/core/db_params.h"
#include "context/db/core/db_response.h"
#include "context/db/core/db_connection.h"

namespace engine {

    class db_request {
    public:
        STL_DELETE_ALL_DEFAULT(db_request)
        STL_DECLARE_NEW_DELETE(db_request)

        using callback = std::function<void(db_response *)>;

        explicit db_request(const std::string_view& query, size_t param_count) noexcept;
        virtual ~db_request();

        void assign_callback(callback&& fn) noexcept;
        void assign_connection(db_connection *connection) noexcept;

        const std::string_view& query() const noexcept { return _query; }
        const db_params& params() const noexcept { return _params; }
        db_connection *connection() noexcept { return _connection; }

    protected:
        db_params               _params;

    private:
        std::string_view        _query;
        db_connection *         _connection;
        callback                _callback;

    };

}

#endif /* ENGINE_DB_REQUEST_H */
