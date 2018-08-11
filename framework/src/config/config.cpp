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
     * config_setting
     */

    config_setting::sptr config_setting::operator[](size_t index) const noexcept
    {
        assert(config_setting_is_aggregate(_setting) == CONFIG_TRUE);
        return config_setting::make_shared(config_setting_get_elem(_setting, static_cast<unsigned int>(index)));
    }

    config_setting::sptr config_setting::operator[](const char *key) const noexcept
    {
        //assert(config_setting_is_group(_setting) == CONFIG_TRUE);
        return config_setting::make_shared(config_setting_get_member(_setting, key));
    }

    bool config_setting::to_bool() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_BOOL);
        return config_setting_get_bool(_setting) != 0;
    }

    s32 config_setting::to_s32() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_INT);
        return config_setting_get_int(_setting);
    }

    s64 config_setting::to_s64() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_INT64);
        return config_setting_get_int64(_setting);
    }

    double config_setting::to_double() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_FLOAT);
        return config_setting_get_float(_setting);
    }

    const char *config_setting::to_string() const noexcept
    {
        assert(config_setting_type(_setting) == CONFIG_TYPE_STRING);
        return config_setting_get_string(_setting);
    }

    size_t config_setting::size() const noexcept
    {
        assert(config_setting_is_aggregate(_setting) == CONFIG_TRUE);
        return static_cast<size_t>(config_setting_length(_setting));
    }

    /**
     * config
     */

    config::config() :
            config_setting(nullptr),
            _config {}
    {
    }

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
            setting(config.root);
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
