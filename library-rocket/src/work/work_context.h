/**
 * @file work_context.h
 * @author Aleksandr Feoktistov
 */
//
// Created by Feo on 16/08/2018.
//

#ifndef ROCKET_WORK_CONTEXT_H
#define ROCKET_WORK_CONTEXT_H

#include "main/rocket_consts.h"
#include "task/task_router.h"
#include "task/task_handler.h"
#include "work/work_loop.h"
#include "work/work_service.h"
#include "work/work_service_delegate.h"

#define RC_CONTEXT_CREATOR(context)                                 \
    [](const groot::setting& config, rocket::task_router *router) { \
        return context::make_unique(config, router);                \
    }

#define RC_BIND_TASK_ROUTE(task, service)                           \
    bind_task_route(task::key(), service::key());

namespace rocket {

    /**
     *
     */
    class work_context : public work_service_delegate, public task_handler {
    public:
        GR_DECLARE_SMARTPOINTERS(work_context)
        GR_DELETE_ALL_DEFAULT(work_context)
        GR_CRUCIAL_BASE_DEFINITION(consts::WORK_CONTEXT_TYPE_MAX_KEY)

        virtual ~work_context() = default;

        /**
         * Start work.
         */
        void start() noexcept;

        /**
         * Stop work.
         */
        void stop() noexcept;

        /**
         * Task acceptance.
         * @param task Task.
         */
        void handle_task(const task::sptr& task) const noexcept final;

        /**
         * Setup services before start.
         */
        void setup_services() noexcept;

        /**
         * Reset services after stop.
         */
        void reset_services() noexcept;

    protected:
        /**
         * Class ctor.
         * @param config Config node with settings regarding concrete work context.
         * @param router Task router. Point to application::_router.
         * @param loop Object to organize event loop inside work context.
         */
        explicit work_context(const groot::setting& config,
                              task_router *router,
                              work_loop::uptr&& loop) noexcept;

        /**
         * Config getter.
         * @return Config node with settings regarding concrete work context.
         */
        const groot::setting& get_config() const noexcept { return _config; }

        /**
         * Task router getter.
         * @return Pointer to task router.
         */
        task_router *get_router() noexcept { return _router; }

        /**
         * Indicate which service must handle concrete task.
         * @param task_key Task key.
         * @param service_key Service key.
         */
        void bind_task_route(task::key_type task_key, work_service::key_type service_key) noexcept;

        /**
         * Add service for own.
         * @param service Service.
         */
        void add_service(work_service::uptr&& service) noexcept;

    private:
        work_loop::uptr                                         _loop;
        const groot::setting&                                   _config;
        task_router *                                           _router;
        std::array<work_service::uptr, work_service::MAX_KEY>   _services;

        /**
         * Store task relation to concrete service.
         * Local (within context) post-route task router.
         */
        std::array<task::key_type, task::MAX_KEY>               _handler_bindings;

        /**
         * Work loop private implementation getter.
         * @see work_service_delegate
         * @return Pointer to work loop.
         */
        work_loop *get_loop_impl() const noexcept final;

        /**
         * Work service private implementation getter.
         * @see work_service_delegate
         * @return Pointer to work service.
         */
        work_service *get_service_impl(groot::crucial_key_type key) const noexcept final;

    };

}

#endif /* ROCKET_WORK_CONTEXT_H */
