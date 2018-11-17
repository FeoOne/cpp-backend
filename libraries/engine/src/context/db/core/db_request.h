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

        using callback = std::function<void(db_request *)>;

        explicit db_request(const char *query, size_t param_count) noexcept;
        virtual ~db_request();

        bool is_callable() const noexcept { return static_cast<bool>(_callback); }

        void assign_callback(callback&& fn) noexcept;
        void assign_connection(db_connection *connection) noexcept;
        void assign_result(PGresult *result) noexcept;

        const char *query() const noexcept { return _query; }
        const db_params& params() const noexcept { return _params; }
        db_connection *connection() noexcept { return _connection; }

        virtual void process_response(db_response *response) noexcept = 0;

        void call() noexcept;
        void refresh() noexcept;

        bool is_success() const noexcept { return _is_success; }

    protected:
        db_params               _params;
        bool                    _is_success;

    private:
        const char *            _query;
        db_connection *         _connection;
        callback                _callback;
        PGresult *              _result;

    };

}

#endif /* ENGINE_DB_REQUEST_H */
