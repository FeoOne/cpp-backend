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

    class execution_context {
    public:
        class service;

        virtual ~execution_context();

        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(execution_context)

    protected:
        execution_context();

    };

    class execution_context::service {
    public:
        virtual ~service() = default;

        virtual void shutdown() noexcept = 0;

        FW_DELETE_DEFAULT_CTOR(service)
        FW_DELETE_DEFAULT_COPY_CTOR(service)
        FW_DELETE_DEFAULT_COPY_ASSIGN(service)

    protected:
        explicit service(execution_context& owner) noexcept : _context { owner } {}

        execution_context& context() noexcept { return _context; }

    private:
        execution_context&      _context;

    };

}

#endif /* ENGINE_EXECUTION_CONTEXT_H */
