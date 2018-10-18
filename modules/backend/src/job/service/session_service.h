/**
 * @file session_service.h
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#ifndef BACKEND_SESSION_SERVICE_H
#define BACKEND_SESSION_SERVICE_H

#include <engine.h>

#include "job/session/database_session.h"

namespace backend {

    class session_service : public stl::crucial<engine::work_service, session_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(session_service)
        STL_DELETE_ALL_DEFAULT(session_service)

        using database_session_manager = engine::session_manager<database_session>;

        explicit session_service(const stl::setting& config,
                                 engine::task_router *router,
                                 const engine::work_service_delegate *delegate) noexcept;
        virtual ~session_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

        inline database_session_manager *database_sessions() noexcept { return _database_sessions.get(); }

    private:
        database_session_manager::uptr  _database_sessions;

    };

}

#endif /* BACKEND_SESSION_SERVICE_H */
