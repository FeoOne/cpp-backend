/**
 * @file db_response.cpp
 * @author Feo
 * @date 14/09/2018
 * @brief
 */

#include "context/db/core/db_types.h"

#include "context/db/core/db_response.h"

namespace engine {

    db_response::db_response(PGresult *result) noexcept :
            _result { result },
            _status { PQresultStatus(result) }
    {
        _is_valid = (_status == PGRES_COMMAND_OK	||
                _status == PGRES_TUPLES_OK		    ||
                _status == PGRES_SINGLE_TUPLE	    ||
                _status == PGRES_NONFATAL_ERROR     ||
                _status == PGRES_FATAL_ERROR);

        if (!_is_valid) {
            logerror("Invalid result: %s", PQresStatus(_status));
        }
    }

    db_response::~db_response()
    {
        PQclear(_result);
    }

    size_t db_response::row_count() const noexcept
    {
        return static_cast<size_t>(PQntuples(_result));
    }

    size_t db_response::column_count() const noexcept
    {
        return static_cast<size_t>(PQnfields(_result));
    }

    std::string_view db_response::column_name(size_t index) const noexcept
    {
        return PQfname(_result, static_cast<int>(index));
    }

    size_t db_response::column_index(const std::string_view& name) const noexcept
    {
        return static_cast<size_t>(PQfnumber(_result, name.data()));
    }

    bool db_response::is_null(size_t row, size_t column) const noexcept
    {
        return PQgetisnull(_result, static_cast<int>(row), static_cast<int>(column)) == 1;
    }

    const char *db_response::result_error_message() const noexcept
    {
        return PQresultErrorMessage(_result);
    }

    void db_response::value(size_t row, size_t column, s64 *val) const noexcept
    {
#ifndef NDEBUG
        auto type { PQftype(_result, static_cast<int>(column)) };
        logassert(type == INT8OID, "Try to get value with wrong format %u.", type);
#endif
        auto pointer { reinterpret_cast<s64 *>(PQgetvalue(_result, static_cast<int>(row), static_cast<int>(column))) };
        *val = static_cast<s64>(ntohll(*pointer));
    }

    void db_response::value(size_t row, size_t column, u64 *val) const noexcept
    {
        value(row, column, reinterpret_cast<s64 *>(val));
    }

    void db_response::value(size_t row, size_t column, s32 *val) const noexcept
    {
#ifndef NDEBUG
        auto type { PQftype(_result, static_cast<int>(column)) };
        logassert(type == INT4OID, "Try to get value with wrong format %u.", type);
#endif
        auto pointer { reinterpret_cast<s32 *>(PQgetvalue(_result, static_cast<int>(row), static_cast<int>(column))) };
        *val = static_cast<s32>(ntohl(*pointer));
    }

    void db_response::value(size_t row, size_t column, u32 *val) const noexcept
    {
        value(row, column, reinterpret_cast<s32 *>(val));
    }

    void db_response::value(size_t row, size_t column, s16 *val) const noexcept
    {
#ifndef NDEBUG
        auto type { PQftype(_result, static_cast<int>(column)) };
        logassert(type == INT2OID, "Try to get value with wrong format %u.", type);
#endif
        auto pointer { reinterpret_cast<s16 *>(PQgetvalue(_result, static_cast<int>(row), static_cast<int>(column))) };
        *val = static_cast<s16>(ntohs(*pointer));
    }

    void db_response::value(size_t row, size_t column, u16 *val) const noexcept
    {
        value(row, column, reinterpret_cast<s16 *>(val));
    }

    void db_response::value(size_t row, size_t column, bool *val) const noexcept
    {
#ifndef NDEBUG
        auto type { PQftype(_result, static_cast<int>(column)) };
        logassert(type == BOOLOID, "Try to get value with wrong format %u.", type);
#endif
        auto pointer { PQgetvalue(_result, static_cast<int>(row), static_cast<int>(column)) };
        *val = *pointer == 1;
    }

    void db_response::value(size_t row, size_t column, char **val) const noexcept
    {
#ifndef NDEBUG
        auto type { PQftype(_result, static_cast<int>(column)) };
        logassert(type == TEXTOID || type == VARCHAROID || type == BPCHAROID,
                  "Try to get value with wrong format %u.", type);
#endif
        *val = PQgetvalue(_result, static_cast<int>(row), static_cast<int>(column));
    }

    void db_response::value(size_t row, size_t column, stl::uuid& val) const noexcept
    {
#ifndef NDEBUG
        auto type { PQftype(_result, static_cast<int>(column)) };
        logassert(type == UUIDOID, "Try to get value with wrong format %u.", type);
#endif
        val.assign(reinterpret_cast<const u8 *>(PQgetvalue(_result, static_cast<int>(row), static_cast<int>(column))));
    }

}
