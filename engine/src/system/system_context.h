/**
 * @file system_context.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_CONTEXT_H
#define ENGINE_SYSTEM_CONTEXT_H

#include "core/execution_context.h"

namespace engine {

    class system_context : public execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(system_context)
        FW_DELETE_ALL_DEFAULT(system_context)

        static constexpr std::string_view NAME { "system" };

        explicit system_context(const framework::config_setting::sptr& config) noexcept;
        ~system_context();

    private:
        std::atomic_bool        _is_should_work;

        void _poll_once() noexcept final;

        void _before_execute() noexcept final;
        void _after_execute() noexcept final;

        bool _should_work() const noexcept final;
        void _should_work(bool b) noexcept final;

    };

}

#endif /* ENGINE_SYSTEM_CONTEXT_H */
