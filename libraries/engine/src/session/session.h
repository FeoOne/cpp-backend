/**
 * @file session.h
 * @author Feo
 * @date 17/10/2018
 * @brief
 */

#ifndef ENGINE_SESSION_H
#define ENGINE_SESSION_H

#include <stl.h>

#include "context/io/task/io_request_task.h"
#include "context/io/task/io_response_task.h"

namespace engine {

    /**
     *
     */
    class session {
    public:
        STL_DECLARE_SMARTPOINTERS(session)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(session)

        session();
        virtual ~session() = default;

        inline bool is_trusted() const noexcept { return _is_trusted; }

        inline const connection_link& link() const noexcept { return _link; }

        virtual void reset(const connection_link& link) noexcept;

    protected:
        inline void trust(bool is_trust) noexcept { _is_trusted = is_trust; }

    private:
        connection_link     _link;
        bool                _is_trusted;

    };

    /**
     *
     */
    class master_session : public session {
    public:
        STL_DECLARE_SMARTPOINTERS(master_session)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(master_session)

        master_session() = default;
        virtual ~master_session() = default;

        void reset(const connection_link& link) noexcept final;

        inline const char *handshake_phrase() noexcept { return _handshake_phrase; }
        bool handshake(const u8 *cipher) noexcept;

    private:
        char        _handshake_phrase[16];

    };

    /**
     *
     */
    class slave_session : public session {
    public:
        STL_DECLARE_SMARTPOINTERS(slave_session)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(slave_session)

        slave_session() = default;
        virtual ~slave_session() = default;

        void reset(const connection_link& link) noexcept final;

    private:

    };

}

#endif /* ENGINE_SESSION_H */
