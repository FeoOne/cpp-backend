/**
 * @file config.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef FRAMEWORK_CONFIG_H
#define FRAMEWORK_CONFIG_H

#include <experimental/optional>

#include <libconfig.h>

#include "memory/memory.h"
#include "string/string.h"
#include "scalar/scalar.h"
#include "util/optional.h"

namespace framework {

    /**
     *
     */
    class config_scope {
    public:
        FW_DECLARE_SMARTPOINTERS(config_scope)

        virtual ~config_scope() = default;

        bool lookup(const std::string_view& key, bool *value) const noexcept;
        bool lookup(const std::string_view& key, s32 *value) const noexcept;
        bool lookup(const std::string_view& key, s64 *value) const noexcept;
        bool lookup(const std::string_view& key, float *value) const noexcept;
        bool lookup(const std::string_view& key, double *value) const noexcept;
        bool lookup(const std::string_view& key, std::string& value) const noexcept;
        bool lookup(const std::string_view& key, config_scope::sptr& value) const noexcept;

        void setting(config_setting_t *s) { _setting = s; }

    protected:
        config_scope() : _setting { nullptr } {}

    private:
        config_setting_t *      _setting;

    };

    /**
     *
     */
    class config : public config_scope {
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
