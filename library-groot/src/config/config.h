/**
 * @file config.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef GROOT_CONFIG_H
#define GROOT_CONFIG_H

#include <cassert>

#include <libconfig.h>

#include "memory/memory.h"
#include "scalar/string.h"
#include "scalar/numeric.h"
#include "util/optional.h"
#include "logger/log_manager.h"

namespace groot {

    /**
     *
     */
    class setting {
    public:
        GR_DELETE_DEFAULT_CTOR(setting)
        GR_DELETE_DEFAULT_MOVE_CTOR(setting)
        GR_DELETE_DEFAULT_MOVE_ASSIGN(setting)

        setting(const setting& other) noexcept : _setting { other._setting } {}
        setting& operator=(const setting& other) { _setting = other._setting; return *this; }

        explicit setting(config_setting_t *other) noexcept : _setting { other } {}
        virtual ~setting() = default;

        setting operator[](size_t index) const noexcept;
        setting operator[](const std::string_view& key) const noexcept;

        bool to_bool() const noexcept;
        s32 to_s32() const noexcept;
        s64 to_s64() const noexcept;
        double to_double() const noexcept;
        const std::string_view to_string() const noexcept;

        bool lookup_bool(const std::string_view& key, bool *value) const noexcept;
        bool lookup_s32(const std::string_view& key, s32 *value) const noexcept;
        bool lookup_s64(const std::string_view& key, s64 *value) const noexcept;
        bool lookup_double(const std::string_view& key, double *value) const noexcept;
        bool lookup_string(const std::string_view& key, const char **value) const noexcept;

        setting root() const noexcept;

        size_t size() const noexcept;

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
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(config)

        config();
        virtual ~config();

        void load(const std::string_view &filename) noexcept;

    private:
        std::unique_ptr<config_t>       _config;

    };

}

#endif /* GROOT_CONFIG_H */
