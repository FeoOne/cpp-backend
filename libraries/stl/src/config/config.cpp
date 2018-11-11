/**
 * @file config.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "logger/log_manager.h"

#include "config/config.h"

namespace stl {

    /**
     * setting
     */

    setting setting::operator[](size_t index) const noexcept
    {
        return setting(config_setting_get_elem(_setting, static_cast<unsigned int>(index)));
    }

    setting setting::operator[](const char *key) const noexcept
    {
        return setting(config_setting_get_member(_setting, key));
    }

    bool setting::to_bool() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_BOOL);
        return config_setting_get_bool(_setting) != 0;
    }

    double setting::to_double() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_FLOAT);
        return config_setting_get_float(_setting);
    }

    const char *setting::to_string() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_STRING);
        return config_setting_get_string(_setting);
    }

    bool setting::lookup_bool(const char *key, bool *value) const noexcept
    {
        int i;
        bool result { false };
        if (config_setting_lookup_bool(_setting, key, &i) == CONFIG_TRUE) {
            *value = (i != CONFIG_FALSE);
            result = true;
        }
        return result;
    }

    bool setting::lookup_double(const char *key, double *value) const noexcept
    {
        return (config_setting_lookup_float(_setting, key, value) == CONFIG_TRUE);
    }

    bool setting::lookup_string(const char *key, const char **value) const noexcept
    {
        return (config_setting_lookup_string(_setting, key, value) == CONFIG_TRUE);
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

    void config::load(const char *filename) noexcept
    {
        lognotice("Loading config from path: '%s'.", filename);

        auto ptr = _config.get();
        config_init(ptr);
        if (config_read_file(ptr, filename) == CONFIG_TRUE) {
            lognotice("Config successfully loaded.");
            assign_setting(ptr->root);
        } else {
            logemerg("Failed to load config.");
        }
    }

}
