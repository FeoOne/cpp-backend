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
        system_context();
        ~system_context();

        void join() noexcept;
        void stop() noexcept;
        bool stopped() const noexcept;

    private:

    };

}

#endif /* ENGINE_SYSTEM_CONTEXT_H */
