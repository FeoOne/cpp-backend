/**
 * @file config.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef STL_CONFIG_H
#define STL_CONFIG_H

#include <cassert>

#include <libconfig.h>

#include "memory/memory.h"
#include "scalar/string.h"
#include "scalar/numeric.h"
#include "util/optional.h"
#include "logger/log_manager.h"

namespace stl {

    /**
     *
     */
    class setting {
    public:
        STL_DELETE_DEFAULT_CTOR(setting)
        STL_DELETE_DEFAULT_MOVE_CTOR(setting)
        STL_DELETE_DEFAULT_MOVE_ASSIGN(setting)

        setting(const setting& other) = default;
        setting& operator=(const setting& other) = default;

        explicit setting(config_setting_t *other) noexcept : _setting { other } {}
        virtual ~setting() = default;

        setting operator[](size_t index) const noexcept;
        setting operator[](const std::string_view& key) const noexcept;

        bool to_bool() const noexcept;
        double to_double() const noexcept;
        const std::string_view to_string() const noexcept;

        template<typename T>
        T to_int32() const noexcept {
            assert(config_setting_type(_setting) == CONFIG_TYPE_INT);
            return static_cast<T>(config_setting_get_int(_setting));
        }

        template<typename T>
        T to_int64() const noexcept {
            assert(config_setting_type(_setting) == CONFIG_TYPE_INT);
            return static_cast<T>(config_setting_get_int64(_setting));
        }

        bool lookup_bool(const std::string_view& key, bool *value) const noexcept;
        bool lookup_double(const std::string_view& key, double *value) const noexcept;
        bool lookup_string(const std::string_view& key, const char **value) const noexcept;

        template<typename T>
        bool lookup_int32(const std::string_view& key, T *value) const noexcept {
            int i;
            bool result { false };
            if (config_setting_lookup_int(_setting, key.data(), &i) == CONFIG_TRUE) {
                *value = static_cast<T>(i);
                result = true;
            }
            return result;
        }

        template<typename T>
        bool lookup_int32(const std::string_view& key, T *value, T default_value) const noexcept {
            int i;
            bool result { false };
            if (config_setting_lookup_int(_setting, key.data(), &i) == CONFIG_TRUE) {
                *value = static_cast<T>(i);
                result = true;
            } else {
                *value = default_value;
            }
            return result;
        }

        template<typename T>
        bool lookup_int64(const std::string_view& key, T *value) const noexcept {
            long long i;
            bool result { false };
            if (config_setting_lookup_int64(_setting, key.data(), &i) == CONFIG_TRUE) {
                *value = static_cast<T>(i);
                result = true;
            }
            return result;
        }

        template<typename T>
        bool lookup_int64(const std::string_view& key, T *value, T default_value) const noexcept {
            long long i;
            bool result { false };
            if (config_setting_lookup_int64(_setting, key.data(), &i) == CONFIG_TRUE) {
                *value = static_cast<T>(i);
                result = true;
            } else {
                *value = default_value;
            }
            return result;
        }

        setting root() const noexcept;

        size_t size() const noexcept;

        bool is_null() const noexcept { return _setting == nullptr; }

    protected:
        void assign_setting(config_setting_t *other) noexcept { _setting = other; }

    private:
        config_setting_t *      _setting;

    };

    /**
     *
     */
    class config : public setting {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(config)

        config();
        virtual ~config();

        void load(const std::string_view &filename) noexcept;

    private:
        std::unique_ptr<config_t>       _config;

    };

}

#endif /* STL_CONFIG_H */
