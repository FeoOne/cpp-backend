/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include <framework.h>

#include "core/execution_context.h"

namespace engine {

    class application {
    public:
        FW_DECLARE_SMARTPOINTERS(application)

        application();
        virtual ~application();

        void load_config(const std::string_view& filename) noexcept;

        void prepare() noexcept;
        void run() noexcept;

    protected:
        virtual void _before_run() noexcept = 0;
        virtual void _after_run() noexcept = 0;

    private:
        using context_vector = std::vector<execution_context::sptr>;
        using context_map = std::unordered_map<std::string_view, execution_context::sptr>;

        framework::config::sptr                 _config;

        context_map                             _context_map;
        context_vector                          _context_vector;

    };

}

#endif /* ENGINE_APPLICATION_H */
