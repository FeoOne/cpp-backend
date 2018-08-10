/**
 * @file socket_options.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_SOCKET_OPTIONS_H
#define ENGINE_SOCKET_OPTIONS_H

#include <cerrno>

#include "network/socket.h"

namespace engine {

    /**
     * SO_DEBUG
     */
    class socket_option_debug final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_debug)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_debug)

        socket_option_debug() : _enabled { false } {}
        explicit socket_option_debug(bool enabled) noexcept : _enabled { enabled } {}
        virtual ~socket_option_debug() = default;

        bool enabled() const noexcept { return _enabled; }
        void enabled(bool enabled) noexcept { _enabled = enabled; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        bool                    _enabled;

    };

    /**
     * SO_LINGER
     */
    class socket_option_linger final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_linger)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_linger)

        socket_option_linger() : _enabled { true }, _timeout { 30 } {}
        explicit socket_option_linger(bool enabled, std::chrono::seconds timeout) noexcept :
                _enabled { enabled },
                _timeout { timeout }
        {}
        virtual ~socket_option_linger() = default;

        bool enabled() const noexcept { return _enabled; }
        void enabled(bool enabled) noexcept { _enabled = enabled; }

        std::chrono::seconds timeout() const noexcept { return _timeout; }
        void timeout(std::chrono::seconds timeout) noexcept  { _timeout = timeout; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        bool                    _enabled;
        std::chrono::seconds    _timeout;

    };

    /**
     * SO_BROADCAST
     */
    class socket_option_broadcast final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_broadcast)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_broadcast)

        socket_option_broadcast() : _enabled { false } {}
        explicit socket_option_broadcast(bool enabled) noexcept : _enabled { enabled } {}
        virtual ~socket_option_broadcast() = default;

        bool enabled() const noexcept { return _enabled; }
        void enabled(bool enabled) noexcept { _enabled = enabled; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        bool                    _enabled;

    };

    /**
     * SO_KEEPALIVE
     */
    class socket_option_keep_alive final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_keep_alive)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_keep_alive)

        socket_option_keep_alive() : _enabled { false } {}
        explicit socket_option_keep_alive(bool enabled) noexcept : _enabled { enabled } {}
        virtual ~socket_option_keep_alive() = default;

        bool enabled() const noexcept { return _enabled; }
        void enabled(bool enabled) noexcept { _enabled = enabled; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        bool                    _enabled;

    };

    /**
     * SO_DONTROUTE
     */
    class socket_option_do_not_route final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_do_not_route)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_do_not_route)

        socket_option_do_not_route() : _enabled { false } {}
        explicit socket_option_do_not_route(bool enabled) noexcept : _enabled { enabled } {}
        virtual ~socket_option_do_not_route() = default;

        bool enabled() const noexcept { return _enabled; }
        void enabled(bool enabled) noexcept { _enabled = enabled; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        bool                    _enabled;

    };

    /**
     * SO_REUSEADDR
     */
    class socket_option_reuse_address final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_reuse_address)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_reuse_address)

        socket_option_reuse_address() : _enabled { false } {}
        explicit socket_option_reuse_address(bool enabled) noexcept : _enabled { enabled } {}
        virtual ~socket_option_reuse_address() = default;

        bool enabled() const noexcept { return _enabled; }
        void enabled(bool enabled) noexcept { _enabled = enabled; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        bool                    _enabled;

    };

    /**
     * SO_OOBINLINE
     */
    class socket_option_out_of_band_inline final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_out_of_band_inline)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_out_of_band_inline)

        socket_option_out_of_band_inline() : _enabled { false } {}
        explicit socket_option_out_of_band_inline(bool enabled) noexcept : _enabled { enabled } {}
        virtual ~socket_option_out_of_band_inline() = default;

        bool enabled() const noexcept { return _enabled; }
        void enabled(bool enabled) noexcept { _enabled = enabled; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        bool                    _enabled;

    };

    /**
     * SO_RCVBUF
     */
    class socket_option_receive_buffer_size final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_receive_buffer_size)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_receive_buffer_size)

        socket_option_receive_buffer_size() : _size { 0 } {}
        explicit socket_option_receive_buffer_size(size_t size) noexcept : _size { size } {}
        virtual ~socket_option_receive_buffer_size() = default;

        size_t size() const noexcept { return _size; }
        void size(size_t size) noexcept { _size = size; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        size_t                  _size;

    };

    /**
     * SO_SNDBUF
     */
    class socket_option_send_buffer_size final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_send_buffer_size)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_send_buffer_size)

        socket_option_send_buffer_size() : _size { 0 } {}
        explicit socket_option_send_buffer_size(size_t size) noexcept : _size { size } {}
        virtual ~socket_option_send_buffer_size() = default;

        size_t size() const noexcept { return _size; }
        void size(size_t size) noexcept { _size = size; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        size_t                  _size;

    };

    /**
     * SO_RCVLOWAT
     */
    class socket_option_receive_low_watermark final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_receive_low_watermark)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_receive_low_watermark)

        socket_option_receive_low_watermark() : _size { 0 } {}
        explicit socket_option_receive_low_watermark(size_t size) noexcept : _size { size } {}
        virtual ~socket_option_receive_low_watermark() = default;

        size_t size() const noexcept { return _size; }
        void size(size_t size) noexcept { _size = size; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        size_t                  _size;

    };

    /**
     * SO_SNDLOWAT
     */
    class socket_option_send_low_watermark final : public socket::gettable_option, public socket::settable_option {
    public:
        FW_DECLARE_SMARTPOINTERS(socket_option_send_low_watermark)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(socket_option_send_low_watermark)

        socket_option_send_low_watermark() : _size { 0 } {}
        explicit socket_option_send_low_watermark(size_t size) noexcept : _size { size } {}
        virtual ~socket_option_send_low_watermark() = default;

        size_t size() const noexcept { return _size; }
        void size(size_t size) noexcept { _size = size; }

        bool get(socket::descriptor_type descriptor) noexcept final;
        void set(socket::descriptor_type descriptor) const noexcept final;

    private:
        size_t                  _size;

    };

}

#endif /* ENGINE_SOCKET_OPTIONS_H */
