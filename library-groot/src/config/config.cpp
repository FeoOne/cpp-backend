/**
 * @file config.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "logger/log_manager.h"

#include "config/config.h"

namespace groot {

    /**
     * setting
     */

    setting setting::operator[](size_t index) const noexcept
    {
        return setting(config_setting_get_elem(_setting, static_cast<unsigned int>(index)));
    }

    setting setting::operator[](const std::string_view& key) const noexcept
    {
        return setting(config_setting_get_member(_setting, key.data()));
    }

    bool setting::to_bool() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_BOOL);
        return config_setting_get_bool(_setting) != 0;
    }

    s32 setting::to_s32() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_INT);
        return config_setting_get_int(_setting);
    }

    s64 setting::to_s64() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_INT64);
        return config_setting_get_int64(_setting);
    }

    double setting::to_double() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_FLOAT);
        return config_setting_get_float(_setting);
    }

    const std::string_view setting::to_string() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_STRING);
        return config_setting_get_string(_setting);
    }

    bool setting::lookup_bool(const std::string_view& key, bool *value) const noexcept
    {
        int i;
        bool result { false };
        if (config_setting_lookup_bool(_setting, key.data(), &i) == CONFIG_TRUE) {
            *value = (i != CONFIG_FALSE);
            result = true;
        }
        return result;
    }

    bool setting::lookup_s32(const std::string_view& key, s32 *value) const noexcept
    {
        return (config_setting_lookup_int(_setting, key.data(), value) == CONFIG_TRUE);
    }

    bool setting::lookup_s64(const std::string_view& key, s64 *value) const noexcept
    {
        long long i;
        bool result { false };
        if (config_setting_lookup_int64(_setting, key.data(), &i) == CONFIG_TRUE) {
            *value = i;
            result = true;
        }
        return result;
    }

    bool setting::lookup_double(const std::string_view& key, double *value) const noexcept
    {
        return (config_setting_lookup_float(_setting, key.data(), value) == CONFIG_TRUE);
    }

    bool setting::lookup_string(const std::string_view& key, const char **value) const noexcept
    {
        return (config_setting_lookup_string(_setting, key.data(), value) == CONFIG_TRUE);
    }

    setting setting::root() const noexcept
    {
        config_setting_t *s = _setting;
        while (!config_setting_is_root(s)) {
            s = s->parent;
        }
        return setting(s);
    }

    size_t setting::size() const noexcept
    {
        assert(config_setting_is_aggregate(_setting) == CONFIG_TRUE);
        return static_cast<size_t>(config_setting_length(_setting));
    }

    /**
     * config
     */

    config::config() :
            setting(nullptr),
            _config { std::make_unique<config_t>() }
    {
    }

    config::~config()
    {
        lognotice("Destroy currently loaded cofig.");
        config_destroy(_config.get());
    }

    void config::load(const std::string_view &filename) noexcept
    {
        lognotice("Loading config from path: '%s'...", filename.data());

        auto ptr = _config.get();
        config_init(ptr);
        if (config_read_file(ptr, filename.data()) == CONFIG_TRUE) {
            lognotice("Config successfully loaded.");
            assign_setting(ptr->root);
        } else {
            logemerg("Failed to load config.");
        }
    }

}
