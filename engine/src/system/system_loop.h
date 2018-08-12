/**
 * @file system_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_LOOP_H
#define ENGINE_SYSTEM_LOOP_H

#include "core/execution_loop.h"

namespace engine {

    class system_loop : public execution_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(system_loop)
        FW_DELETE_ALL_DEFAULT(system_loop)

        explicit system_loop(const event_queue::sptr& queue) noexcept;
        virtual ~system_loop();

        void run() noexcept final;
        void stop() noexcept final;

        bool stopped() const noexcept final;

    private:
        std::atomic_bool        _is_stopped;
        std::atomic_bool        _should_work;

    };

}

#endif /* ENGINE_SYSTEM_LOOP_H */
