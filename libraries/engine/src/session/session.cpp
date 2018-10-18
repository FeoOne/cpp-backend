/**
 * @file session.cpp
 * @author Feo
 * @date 17/10/2018
 * @brief
 */

#include "session/session.h"

namespace engine {

    session::session() :
            _link {},
            _is_trusted { false }
    {

    }

    // virtual
    void session::reset(const connection_link& link) noexcept
    {
        _link = link;
    }

    /**
     * master_session
     */

    // virtual
    void master_session::reset(const connection_link& link) noexcept
    {
        session::reset(link);

        trust(false);
        stl::string::fill_with_random_symbols(_handshake_phrase, sizeof(_handshake_phrase) - 1);
    }

    bool master_session::handshake(const u8 *cipher) noexcept
    {
        stl::md5_hash::uptr md5 { stl::md5_hash::make_unique() };
        md5->update(_handshake_phrase);
        md5->finalize();

        bool result { std::memcmp(cipher, md5->digest(), md5->digest_length) == 0 };
        trust(result);

        return result;
    }

    /**
     * slave_session
     */

    // virtual
    void slave_session::reset(const connection_link& link) noexcept
    {
        session::reset(link);

        trust(true);
    }

}
