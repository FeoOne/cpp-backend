/**
 * @file session_manager.h
 * @author Feo
 * @date 17/10/2018
 * @brief
 */

#ifndef ENGINE_SESSION_MANAGER_H
#define ENGINE_SESSION_MANAGER_H

#include <stl.h>

#include "session/session.h"
#include "context/io/connection/connection_link.h"

namespace engine {

    template<typename T>
    class session_manager {
    public:
        STL_DECLARE_SMARTPOINTERS(session_manager<T>)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(session_manager)

        using value_type = T;
        using pointer_type = T *;

        session_manager() : _sessions {}, _pool { session_pool::make_unique() } {}
        ~session_manager() {}

        T *create(const connection_link& link) noexcept {
            STL_UNIQUE_LOCK(lock, _mutex);

            auto session { _pool->acquire() };
            session->reset(link);

            _sessions[link] = session;

            return session;
        }

        void destroy(const connection_link& link) noexcept {
            STL_UNIQUE_LOCK(lock, _mutex);

            auto it = _sessions.find(link);
            if (it != _sessions.end()) {
                _pool->release(it->second);
                _sessions.erase(it);
            } else {
                logerror("Can not find session for cid: %llu.", link.connection_id());
            }
        }

        T *get(const connection_link& link) noexcept {
            STL_UNIQUE_LOCK(lock, _mutex);

            pointer_type session { nullptr };

            auto it { _sessions.find(link) };
            if (it != _sessions.end()) {
                session = _sessions[link];
            }

            return session;
        }

    private:
        using session_pool = stl::object_pool<value_type>;

        std::unordered_map<connection_link, pointer_type>   _sessions;
        typename session_pool::uptr                         _pool;

        std::timed_mutex                                    _mutex;

    };

}

#endif /* ENGINE_SESSION_MANAGER_H */
