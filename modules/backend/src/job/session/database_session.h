/**
 * @file database_session.h
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#ifndef BACKEND_DATABASE_SESSION_H
#define BACKEND_DATABASE_SESSION_H

#include <engine.h>

namespace backend {

    class database_session : public engine::slave_session {
    public:
        STL_DECLARE_SMARTPOINTERS(database_session)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(database_session)

        database_session() = default;
        virtual ~database_session() = default;

    private:

    };

}

#endif /* BACKEND_DATABASE_SESSION_H */
