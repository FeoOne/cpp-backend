/**
 * @file socket.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_SOCKET_H
#define ENGINE_SOCKET_H

#include <chrono>

#include <sys/types.h>
#include <sys/socket.h>

#include <framework.h>

namespace engine {

    /**
     *
     */
    class socket {
    public:
        FW_DECLARE_SMARTPOINTERS(socket)

        using descriptor_type = int;

        class gettable_option;
        class settable_option;

        virtual ~socket() = default;

        descriptor_type descriptor() const noexcept { return _descriptor; }

        template<typename T>
        bool get_option(typename T::sptr& option) const noexcept {
            return option->get(_descriptor);
        }

        template<typename T>
        void set_option(const typename T::sptr& option) const noexcept {
            option->set(_descriptor);
        }

        void non_blocking(bool mode) const noexcept;
        bool non_blocking() const noexcept;

        //void connect()

    protected:
        socket() : _descriptor { -1 } {}

    private:
        descriptor_type         _descriptor;

    };

    /**
     *
     */
    class socket::gettable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(gettable_option)

        virtual ~gettable_option() = default;

        virtual bool get(socket::descriptor_type handle) noexcept = 0;
    };

    /**
     *
     */
    class socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(settable_option)

        virtual ~settable_option() = default;

        virtual void set(socket::descriptor_type handle) const noexcept = 0;
    };

    /**
     *
     */
    class basic_socket : public socket {
    public:
        FW_DECLARE_SMARTPOINTERS(basic_socket)

    };

    /**
     *
     */
    class stream_socket : public basic_socket {
    public:
        FW_DECLARE_SMARTPOINTERS(stream_socket)

    };

    /**
     *
     */
    class datagram_socket : public basic_socket {
    public:
        FW_DECLARE_SMARTPOINTERS(datagram_socket)

    };

}

#endif /* ENGINE_SOCKET_H */
