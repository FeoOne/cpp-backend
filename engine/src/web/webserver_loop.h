//
// Created by Feo on 17/08/2018.
//

#ifndef ENGINE_WEBSERVER_LOOP_H
#define ENGINE_WEBSERVER_LOOP_H

#include <uv.h>

#include "work/work_loop.h"

namespace engine {

    class webserver_loop : public work_loop {
    public:
        FW_DECLARE_SMARTPOINTERS(webserver_loop)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(webserver_loop)

        webserver_loop();
        virtual ~webserver_loop();

        void start() noexcept final;
        void stop() noexcept final;

    private:
        uv_loop_t           _loop;
        uv_async_t          _wakeup_handle;

        void on_wakeup() noexcept;

        static void wakeup_routine(uv_async_t *async_handle) noexcept;

    };

}

#endif /* ENGINE_WEBSERVER_LOOP_H */
