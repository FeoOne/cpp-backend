//
// Created by Feo on 25/10/2018.
//

#include "context/db/core/db_types.h"

#include "context/db/core/db_params.h"

namespace engine {

    db_params::db_params(size_t count) noexcept :
            _count { count },
            _values {},
            _lengths {},
            _formats {},
            _oids {},
            _memory { nullptr },
            _length { 0 }
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
        if (_memory != nullptr) {
            std::free(_memory);
        }
    }

    const char *db_params::values() const noexcept
    {
        return count() != 0 ? reinterpret_cast<char *>(_memory) : nullptr;
    }

    const int *db_params::lengths() const noexcept
    {
        return count() != 0 ? _lengths.data() : nullptr;
    }

    const int *db_params::formats() const noexcept
    {
        return count() != 0 ? _formats.data() : nullptr;
    }

    const Oid *db_params::oids() const noexcept
    {
        return count() != 0 ? _oids.data() : nullptr;
    }

    void db_params::bake() noexcept
    {
        _memory = stl::memory::malloc<u8>(_length);

        size_t offset { 0 };
        for (size_t i = 0; i < _count; ++i) {
            auto memory { &_memory[offset] };

            switch (_oids[i]) {
                case BOOLOID:
                case TEXTOID:
                case UUIDOID: {
                    std::memcpy(memory, _values[i], static_cast<size_t>(_lengths[i]));
                    break;
                }
                case INT2OID: {
                    u16 value { htobe16(*reinterpret_cast<const u16 *>(_values[i])) };
                    std::memcpy(memory, &value, static_cast<size_t>(_lengths[i]));
                    break;
                }
                case INT4OID: {
                    u32 value { htobe32(*reinterpret_cast<const u32 *>(_values[i])) };
                    std::memcpy(memory, &value, static_cast<size_t>(_lengths[i]));
                    break;
                }
                case INT8OID: {
                    u64 value { htobe64(*reinterpret_cast<const u64 *>(_values[i])) };
                    std::memcpy(memory, &value, static_cast<size_t>(_lengths[i]));
                    break;
                }
                case FLOAT4OID: {
                    u8 value[sizeof(float)];
                    std::memcpy(value, _values[i], sizeof(float));
                    std::reverse(std::begin(value), std::end(value));
                    std::memcpy(memory, value, static_cast<size_t>(_lengths[i]));
                    break;
                }
                case FLOAT8OID: {
                    u8 value[sizeof(double)];
                    std::memcpy(value, _values[i], sizeof(double));
                    std::reverse(std::begin(value), std::end(value));
                    std::memcpy(memory, value, static_cast<size_t>(_lengths[i]));
                    break;
                }
                default: {
                    break;
                }
            }

            offset += static_cast<size_t>(_lengths[i]);
        }

        logassert(offset == _length, "Bake problem.");
    }

    void db_params::operator<<(const std::string& value) noexcept
    {
        append(value.data(), value.length() + 1, FORMAT_BINARY, TEXTOID);
    }

    void db_params::operator<<(const char *value) noexcept
    {
        append(value, std::strlen(value) + 1, FORMAT_BINARY, TEXTOID);
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

        _values.push_back(memory);
        _lengths.push_back(static_cast<int>(length));
        _formats.push_back(format);
        _oids.push_back(oid);

        _length += length;
    }

}
