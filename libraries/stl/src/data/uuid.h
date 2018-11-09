/**
 * @file uuid.h
 * @author Feo
 * @date 24/08/2018
 * @brief
 */

#ifndef STL_UUID_H
#define STL_UUID_H

#include <uuid/uuid.h>

#include "memory/memory.h"
#include "scalar/string.h"
#include "scalar/numeric.h"

namespace stl {

    class uuid {
    public:
        STL_DECLARE_SMARTPOINTERS(uuid)
        STL_DELETE_DEFAULT_MOVE_CTOR(uuid)
        STL_DELETE_DEFAULT_MOVE_ASSIGN(uuid)

        using uuid_type = uuid_t;

        enum class generate_strategy {
            PLAIN,
            RANDOM,
            TIME,
        };

        uuid() { uuid_clear(_uuid); }
        explicit uuid(generate_strategy strategy) noexcept { generate(strategy); }
        explicit uuid(const u8 *data) noexcept { uuid_copy(_uuid, data); }
        explicit uuid(const char *str) noexcept { parse(str); }
        explicit uuid(const std::string& str) noexcept { parse(str.c_str()); }
        explicit uuid(const std::string_view& str) noexcept { parse(str.data()); }

        uuid(const uuid& other) { uuid_copy(_uuid, other._uuid); }
        uuid& operator=(const uuid& other) { uuid_copy(_uuid, other._uuid); return *this; }

        bool operator==(const uuid& other) const noexcept { return (uuid_compare(_uuid, other._uuid) == 0); }
        bool operator!=(const uuid& other) const noexcept { return (uuid_compare(_uuid, other._uuid) != 0); }

        bool is_null() const noexcept { return (uuid_is_null(_uuid) == 1); }

        const u8 *data() const noexcept {
            return reinterpret_cast<const u8 *>(_uuid);
        }

        size_t hash() const noexcept {
            return *reinterpret_cast<const size_t *>(&_uuid[0]) ^
                   *reinterpret_cast<const size_t *>(&_uuid[8]);
        }

    private:
        uuid_type   _uuid;

        void generate(generate_strategy strategy) noexcept {
            switch (strategy) {
                case generate_strategy::PLAIN: uuid_generate(_uuid); break;
                case generate_strategy::RANDOM: uuid_generate_random(_uuid); break;
                case generate_strategy::TIME: uuid_generate_time(_uuid); break;
            }
        }

        void parse(const char *str) {
            uuid_parse(str, _uuid);
        }

    };

}

namespace std {

    template<>
    struct hash<stl::uuid> {
        size_t operator()(const stl::uuid& guid) const noexcept {
            return guid.hash();
        }
    };

}

#endif /* STL_UUID_H */
