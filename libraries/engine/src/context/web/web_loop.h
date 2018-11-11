/**
 * @file web_loop.h
 * @author Feo
 * @date 17/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSERVER_LOOP_H
#define ENGINE_WEBSERVER_LOOP_H

#include <uv.h>

#include "work/work_loop.h"

namespace engine {

    class web_loop : public work_loop {
    public:
        STL_DECLARE_SMARTPOINTERS(web_loop)
        STL_DELETE_ALL_DEFAULT(web_loop)

        explicit web_loop(task_queue *queue, const task_handler *handler) noexcept;
        virtual ~web_loop();

        void start() noexcept final;
        void stop() noexcept final;

    private:
        GMainLoop *                 _loop;

        gboolean on_idle() noexcept;

        static gboolean idle_callback(gpointer pointer) noexcept;

    };

}

#endif /* ENGINE_WEBSERVER_LOOP_H */
