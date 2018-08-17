//
// Created by Feo on 16/08/2018.
//

#ifndef ENGINE_WORK_CONTEXT_H
#define ENGINE_WORK_CONTEXT_H

#include <framework.h>

#include "work/work_loop.h"
#include "task/task_router.h"

namespace engine {

    class work_context {
    public:
        FW_DECLARE_SMARTPOINTERS(work_context)
        FW_DELETE_ALL_DEFAULT(work_context)
        FW_CRUCIAL_BASE_DEFINITION()

        explicit work_context(const framework::config_setting::sptr& config,
                              const task_router::sptr& router,
                              work_loop::uptr&& loop) noexcept;
        virtual ~work_context() = default;

        void start() noexcept;
        void stop() noexcept;

    protected:
        framework::config_setting::sptr get_config() const noexcept { return _config; }
        task_router::sptr get_router() const noexcept { return _router; }

    private:
        framework::config_setting::sptr     _config;
        task_router::sptr                   _router;
        work_loop::uptr                     _loop;

    };

}

#endif /* ENGINE_WORK_CONTEXT_H */
