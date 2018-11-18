//
// Created by Feo on 25/10/2018.
//

#include "context/db/core/db_types.h"

#include "context/db/core/db_params.h"

#define EX_MEM_POOL_SIZE    4194304

namespace engine {

    // static
    stl::float_memory_pool::uptr db_params::_memory_pool { stl::float_memory_pool::make_unique(EX_MEM_POOL_SIZE) };

    db_params::db_params(size_t count) noexcept :
            _count { count },
            _values {},
            _lengths {},
            _formats {},
            _oids {}
    {
        if (count > 0) {
            _values.reserve(count);
            _lengths.reserve(count);
            _formats.reserve(count);
            _oids.reserve(count);
        }
    }

    db_params::~db_params()
    {
        for (auto memory: _values) {
            _memory_pool->free(memory);
        }
    }

    const char * const *db_params::values() const noexcept
    {
        return _count != 0 ? _values.data() : nullptr;
    }

    const int *db_params::lengths() const noexcept
    {
        return _count != 0 ? _lengths.data() : nullptr;
    }

    const int *db_params::formats() const noexcept
    {
        return _count != 0 ? _formats.data() : nullptr;
    }

    const Oid *db_params::oids() const noexcept
    {
        return _count != 0 ? _oids.data() : nullptr;
    }

    void db_params::operator<<(const std::string& value) noexcept
    {
        append(value.data(), value.length() + 1, FORMAT_TEXT, TEXTOID);
    }

    void db_params::operator<<(const char *value) noexcept
    {
        append(value, std::strlen(value) + 1, FORMAT_TEXT, TEXTOID);
    }

    void db_params::operator<<(bool value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, BOOLOID);
    }

    void db_params::operator<<(u16 value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, INT2OID);
    }

    void db_params::operator<<(s16 value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, INT2OID);
    }

    void db_params::operator<<(u32 value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, INT4OID);
    }

    void db_params::operator<<(s32 value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, INT4OID);
    }

    void db_params::operator<<(u64 value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, INT8OID);
    }

    void db_params::operator<<(s64 value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, INT8OID);
    }

    void db_params::operator<<(float value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, FLOAT4OID);
    }

    void db_params::operator<<(double value) noexcept
    {
        append(reinterpret_cast<const char *>(&value), sizeof(value), FORMAT_BINARY, FLOAT8OID);
    }

    void db_params::operator<<(const stl::uuid& value) noexcept
    {
        append(reinterpret_cast<const char *>(value.data()), sizeof(stl::uuid::uuid_type), FORMAT_BINARY, UUIDOID);
    }

    void db_params::append(const char *memory, size_t length, int format, Oid oid) noexcept
    {
        logassert(_values.size() < _count, "Wrong param count.");

        char *data { reinterpret_cast<char *>(_memory_pool->alloc(length)) };
        switch (oid) {
            case BOOLOID:
            case TEXTOID:
            case UUIDOID: {
                std::memcpy(data, memory, length);
                break;
            }
            case INT2OID: {
                logassert(length == sizeof(u16), "Param length missmatch.");
                u16 value { htobe16(*reinterpret_cast<const u16 *>(memory)) };
                std::memcpy(data, &value, sizeof(u16));
                break;
            }
            case INT4OID: {
                logassert(length == sizeof(u32), "Param length missmatch.");
                u32 value { htobe32(*reinterpret_cast<const u32 *>(memory)) };
                std::memcpy(data, &value, sizeof(u32));
                break;
            }
            case INT8OID: {
                logassert(length == sizeof(u64), "Param length missmatch.");
                u64 value { htobe64(*reinterpret_cast<const u64 *>(memory)) };
                std::memcpy(data, &value, sizeof(u64));
                break;
            }
            case FLOAT4OID: {
                logassert(length == sizeof(float), "Param length missmatch.");
                u8 value[sizeof(float)];
                std::memcpy(value, memory, sizeof(float));
                std::reverse(std::begin(value), std::end(value));
                std::memcpy(data, value, sizeof(float));
                break;
            }
            case FLOAT8OID: {
                logassert(length == sizeof(double), "Param length missmatch.");
                u8 value[sizeof(double)];
                std::memcpy(value, memory, sizeof(double));
                std::reverse(std::begin(value), std::end(value));
                std::memcpy(data, value, sizeof(double));
                break;
            }
            default: {
                break;
            }
        }

        _values.push_back(data);
        _lengths.push_back(static_cast<int>(length));
        _formats.push_back(format);
        _oids.push_back(oid);
    }

}

#undef EX_MEM_POOL_SIZE
