/**
 * @file web_server_loop.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_SERVER_LOOP_H
#define ENGINE_WEB_SERVER_LOOP_H

#include <glib/gstdio.h>

#include "work/work_loop.h"

namespace engine {

    class web_server_loop final : public work_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_loop)
        FW_DELETE_ALL_DEFAULT(web_server_loop)

        explicit web_server_loop(const event_queue::sptr& queue) noexcept;
        virtual ~web_server_loop();

        void run() noexcept final;
        void stop() noexcept final;

        bool stopped() const noexcept final;

    private:
        GMainLoop *                 _loop;
        std::atomic_bool            _should_work;

        gboolean on_idle() noexcept;

        static gboolean on_idle(gpointer pointer) noexcept;

    };

}

#endif /* ENGINE_WEB_SERVER_LOOP_H */
