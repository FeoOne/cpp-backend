//
// Created by Feo on 17/08/2018.
//

#ifndef ROCKET_WEBSERVER_LOOP_H
#define ROCKET_WEBSERVER_LOOP_H

#include <uv.h>

#include "work/work_loop.h"

namespace rocket {

    class webserver_loop : public work_loop {
    public:
        GR_DECLARE_SMARTPOINTERS(webserver_loop)
        GR_DELETE_ALL_DEFAULT(webserver_loop)

        explicit webserver_loop(const task_queue::sptr& queue, task_handler *handler) noexcept;
        virtual ~webserver_loop();

        void start() noexcept final;
        void stop() noexcept final;

    private:
        GMainLoop *                 _loop;

        gboolean on_idle() noexcept;

        static gboolean idle_routine(gpointer pointer) noexcept;

    };

}

#endif /* ROCKET_WEBSERVER_LOOP_H */
