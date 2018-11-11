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
        STL_DELETE_ALL_DEFAULT(db_params)

        explicit db_params(size_t count) noexcept;

        ~db_params();

        size_t count() const noexcept { return _count; }
        const char * const *values() const noexcept;
        const int *lengths() const noexcept;
        const int *formats() const noexcept;
        const Oid *oids() const noexcept;

        void bake() noexcept;

        void operator<<(const std::string& value) noexcept;
        void operator<<(const std::string_view& value) noexcept;
        void operator<<(bool value) noexcept;
        void operator<<(u16 value) noexcept;
        void operator<<(s16 value) noexcept;
        void operator<<(u32 value) noexcept;
        void operator<<(s32 value) noexcept;
        void operator<<(u64 value) noexcept;
        void operator<<(s64 value) noexcept;
        void operator<<(float value) noexcept;
        void operator<<(double value) noexcept;
        void operator<<(const stl::uuid& value) noexcept;

    private:
        size_t                          _count;
        std::vector<const char *>       _values;
        std::vector<int>                _lengths;
        std::vector<int>                _formats;
        std::vector<Oid>                _oids;

        u8 *                            _memory;
        size_t                          _length;

        void append(const char *memory, size_t length, int format, Oid oid) noexcept;

    };

}

#endif /* ENGINE_DB_PARAMS_H */
