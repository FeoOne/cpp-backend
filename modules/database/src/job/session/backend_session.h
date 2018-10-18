/**
 * @file backend_session.h
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#ifndef DATABASE_BACKEND_SESSION_H
#define DATABASE_BACKEND_SESSION_H

#include <engine.h>

namespace database {

    class backend_session : public engine::master_session {
    public:
        STL_DECLARE_SMARTPOINTERS(backend_session)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(backend_session)

        backend_session() = default;
        virtual ~backend_session() = default;

    private:

    };

}

#endif /* DATABASE_BACKEND_SESSION_H */
