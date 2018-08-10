/**
 * @file execution_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_CONTEXT_H
#define ENGINE_EXECUTION_CONTEXT_H

#include <framework.h>

namespace engine {

    enum class fork_event_t {
        PREPARE,
        PARENT,
        CHILD,
    };

    class execution_context {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_context)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(execution_context)

        class service;

        virtual ~execution_context();

        void notify_fork(fork_event_t event) noexcept;

    protected:
        execution_context();

    private:
        std::vector<service>        _services;

        void shutdown() noexcept;
        void destroy() noexcept;

    };

    class execution_context::service {
    public:
        FW_DECLARE_SMARTPOINTERS(service)
        FW_DELETE_ALL_DEFAULT(service)

        virtual ~service() = default;

        virtual void notify_fork(fork_event_t event) noexcept = 0;
        virtual void shutdown() noexcept = 0;

    protected:
        explicit service(execution_context& owner) noexcept : _context { owner } {}

        execution_context& context() noexcept { return _context; }

    private:
        execution_context&      _context;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
