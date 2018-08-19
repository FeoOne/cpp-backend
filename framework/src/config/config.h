/**
 * @file config.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef FRAMEWORK_CONFIG_H
#define FRAMEWORK_CONFIG_H

#include <cassert>

#include <libconfig.h>

#include "memory/memory.h"
#include "string/string.h"
#include "scalar/scalar.h"
#include "util/optional.h"
#include "logger/log_manager.h"

namespace framework {

    /**
     *
     */
    class config_setting {
    public:
        FW_DECLARE_SMARTPOINTERS(config_setting)
        FW_DELETE_ALL_DEFAULT(config_setting)

        explicit config_setting(config_setting_t *setting) noexcept : _setting { setting } {}
        virtual ~config_setting() = default;

        config_setting::sptr operator[](size_t index) const noexcept;
        config_setting::sptr operator[](const char *key) const noexcept;
        config_setting::sptr operator[](const std::string_view& key) const noexcept;

        bool to_bool() const noexcept;
        s32 to_s32() const noexcept;
        s64 to_s64() const noexcept;
        double to_double() const noexcept;
        const char *to_string() const noexcept;
        std::string_view to_string_view() const noexcept;

        bool lookup_bool(const char *key, bool *value) const noexcept;
        bool lookup_s32(const char *key, s32 *value) const noexcept;
        bool lookup_s64(const char *key, s64 *value) const noexcept;
        bool lookup_double(const char *key, double *value) const noexcept;
        bool lookup_string(const char *key, const char **value) const noexcept;

        config_setting::sptr root() const noexcept;

        size_t size() const noexcept;

    protected:
        void setting(config_setting_t *setting) noexcept { _setting = setting; }

    private:
        config_setting_t *      _setting;

    };

    /**
     *
     */
    class config : public config_setting {
    public:
        FW_DECLARE_SMARTPOINTERS(config)

        config();
        virtual ~config();

        void read(const std::string_view& filename) noexcept;

    private:
        optional<config_t>          _config;

        void destroy() noexcept;

    };

}

#endif /* FRAMEWORK_CONFIG_H */
