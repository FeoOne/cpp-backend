//
// Created by Feo on 25/10/2018.
//

#include "context/db/core/db_params.h"

namespace engine {

    db_params::db_params() :
            _count { 0 },
            _values {},
            _lengths {},
            _formats {},
            _oids {},
            _memory { nullptr },
            _length { 0 },
            _position { 0 }
    {
    }

    db_params::db_params(size_t count) noexcept :
            _count { count },
            _values {},
            _lengths {},
            _formats {},
            _oids {},
            _memory { nullptr },
            _length { 0 },
            _position { 0 }
    {
        if (count > 0) {
            _values.reserve(count);
            _lengths.reserve(count);
            _formats.reserve(count);
            _oids.reserve(count);
        }
    }

    void db_params::append(const char *memory, int length, int format, Oid oid) noexcept
    {
        _values.push_back(memory);
        _lengths.push_back(length);
        _formats.push_back(format);
        _oids.push_back(oid);

        _length += static_cast<size_t>(length);
    }

}
