/**
 * @file session_service.h
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#ifndef DATABASE_SESSION_SERVICE_H
#define DATABASE_SESSION_SERVICE_H

#include <engine.h>

#include "job/session/backend_session.h"

namespace database {

    class session_service : public stl::crucial<engine::work_service, session_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(session_service)
        STL_DELETE_ALL_DEFAULT(session_service)

        using backend_session_manager = engine::session_manager<backend_session>;

        explicit session_service(const stl::setting& config,
                                 engine::task_router *router,
                                 const engine::work_service_delegate *delegate) noexcept;
        virtual ~session_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

        inline backend_session_manager *backend_sessions() noexcept { return _backend_sessions.get(); }

    private:
        static backend_session_manager::uptr    _backend_sessions;

    };

}

#endif /* DATABASE_SESSION_SERVICE_H */
