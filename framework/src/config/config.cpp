/**
 * @file config.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "logger/log_manager.h"

#include "config/config.h"

namespace framework {

    /**
     * config_scope
     */

    bool config_scope::lookup(const std::string_view& key, bool *value) const noexcept
    {
        bool result { false };

        int val;
        if (config_setting_lookup_bool(_setting, key.data(), &val) == CONFIG_TRUE) {
            *value = (val == CONFIG_TRUE);
            result = true;
        }

        return result;
    }

    bool config_scope::lookup(const std::string_view& key, s32 *value) const noexcept
    {
        bool result { false };

        int val;
        if (config_setting_lookup_int(_setting, key.data(), &val) == CONFIG_TRUE) {
            *value = static_cast<s32>(val);
            result = true;
        }

        return result;
    }

    bool config_scope::lookup(const std::string_view& key, s64 *value) const noexcept
    {
        bool result { false };

        long long val;
        if (config_setting_lookup_int64(_setting, key.data(), &val) == CONFIG_TRUE) {
            *value = static_cast<s64>(val);
            result = true;
        }

        return result;
    }

    bool config_scope::lookup(const std::string_view& key, float *value) const noexcept
    {
        bool result { false };

        double val;
        if (config_setting_lookup_float(_setting, key.data(), &val) == CONFIG_TRUE) {
            *value = static_cast<float>(val);
            result = true;
        }

        return result;
    }

    bool config_scope::lookup(const std::string_view& key, double *value) const noexcept
    {
        return (config_setting_lookup_float(_setting, key.data(), value) == CONFIG_TRUE);
    }

    bool config_scope::lookup(const std::string_view& key, std::string& value) const noexcept
    {
        bool result { false };

        const char *val;
        if (config_setting_lookup_string(_setting, key.data(), &val) == CONFIG_TRUE) {
            value.assign(val);
            result = true;
        }

        return result;
    }

    bool config_scope::lookup(const std::string_view& key, config_scope::sptr& value) const noexcept
    {
        bool result { false };

        auto setting = config_setting_lookup(_setting, key.data());
        if (setting != nullptr) {
            value->setting(setting);
            result = true;
        }

        return result;
    }

    config::config() :
            _config {}
    {
    }

    /**
     * config
     */

    config::~config()
    {
        destroy();
    }

    void config::read(const std::string_view& filename) noexcept
    {
        destroy();

        config_t config;
        config_init(&config);
        if (config_read_file(&config, filename.data()) == CONFIG_TRUE) {
            _config.value(config);
        } else {
            logcrit("Failed to load log: %s", filename.data());
        }
    }

    void config::destroy() noexcept
    {
        if (_config.is_set()) {
            config_destroy(_config.pointer());
            _config.reset();
        }
    }

}
