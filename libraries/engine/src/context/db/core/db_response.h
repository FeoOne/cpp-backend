/**
 * @file db_response.h
 * @author Feo
 * @date 14/09/2018
 * @brief
 */

#ifndef ENGINE_DB_RESPONSE_H
#define ENGINE_DB_RESPONSE_H

#include <libpq-fe.h>

#include <stl.h>

namespace engine {

    class db_response {
    public:
        explicit db_response(PGresult *result) noexcept;
        ~db_response();

        bool is_valid() const noexcept { return _is_valid; }
        ExecStatusType status() const noexcept { return _status; }
        PGresult *result() noexcept { return _result; }

        size_t row_count() const noexcept;
        size_t column_count() const noexcept;
        std::string_view column_name(size_t index) const noexcept;
        size_t column_index(const std::string_view& name) const noexcept;
        bool is_null(size_t row, size_t column) const noexcept;

        const char *result_error_message() const noexcept;

        void value(size_t row, size_t column, s64 *val) const noexcept;
        void value(size_t row, size_t column, u64 *val) const noexcept;
        void value(size_t row, size_t column, s32 *val) const noexcept;
        void value(size_t row, size_t column, u32 *val) const noexcept;
        void value(size_t row, size_t column, s16 *val) const noexcept;
        void value(size_t row, size_t column, u16 *val) const noexcept;
        void value(size_t row, size_t column, bool *val) const noexcept;
        void value(size_t row, size_t column, char **val) const noexcept;
        void value(size_t row, size_t column, stl::uuid& val) const noexcept;

    private:
        PGresult *          _result;
        ExecStatusType      _status;
        bool                _is_valid;

    };

}

#endif /* ENGINE_DB_RESPONSE_H */
