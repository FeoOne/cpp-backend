//
// Created by Feo on 25/10/2018.
//

#ifndef ENGINE_DB_PARAMS_H
#define ENGINE_DB_PARAMS_H

#include <stl.h>

#include <libpq-fe.h>

namespace engine {

    class db_params final {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(db_params)

        db_params();
        explicit db_params(size_t count) noexcept;

        ~db_params() = default;

    private:
        size_t                          _count;
        std::vector<const char *>       _values;
        std::vector<int>                _lengths;
        std::vector<int>                _formats;
        std::vector<Oid>                _oids;

        u8 *                            _memory;
        size_t                          _length;
        size_t                          _position;

        void append(const char *memory, int length, int format, Oid oid) noexcept;

    };

}

#endif /* ENGINE_DB_PARAMS_H */
