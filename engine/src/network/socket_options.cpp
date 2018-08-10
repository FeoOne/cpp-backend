/**
 * @file socket_options.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include <sys/types.h>
#include <sys/socket.h>

#include "network/socket_options.h"

#define check_get_result(result, optname, action)                                               \
    if (result != 0) {                                                                          \
        logwarn("Failed to get " FW_STR(optname) " option (%d, %s).", errno, strerror(errno));  \
    } else { action }

#define check_set_result(result, optname, optval)                                                           \
    if (result != 0) {                                                                                      \
        logwarn("Failed to set " FW_STR(optname) " (%d) option (%d, %s).", optval, errno, strerror(errno)); \
    }

namespace engine {

    // virtual
    bool socket_option_debug::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen { sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_DEBUG, &optval, &optlen);
        check_get_result(get_result, SO_DEBUG, {
            result = true;
            _enabled = (optval != 0);
        });
        return result;
    }

    // virtual
    void socket_option_debug::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = _enabled ? 1 : 0;
        int result = setsockopt(descriptor, SOL_SOCKET, SO_DEBUG, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_DEBUG, opt);
    }

    // virtual
    bool socket_option_linger::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        linger optval { 1, 30 };
        socklen_t optlen { sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_LINGER, &optval, &optlen);
        check_get_result(get_result, SO_LINGER, {
            result = true;
            _enabled = (optval.l_onoff != 0);
            _timeout =  std::chrono::seconds(optval.l_linger);
        });
        return result;
    }

    // virtual
    void socket_option_linger::set(socket::descriptor_type descriptor) const noexcept
    {
        linger opt {
            _enabled ? 1 : 0,
            static_cast<int>(std::chrono::seconds(_timeout).count())
        };
        int result = setsockopt(descriptor, SOL_SOCKET, SO_LINGER, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_LINGER, opt.l_linger);
    }

    // virtual
    bool socket_option_broadcast::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_BROADCAST, &optval, &optlen);
        check_get_result(get_result, SO_BROADCAST, {
            result = true;
            _enabled = (optval != 0);
        });
        return result;
    }

    // virtual
    void socket_option_broadcast::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = _enabled ? 1 : 0;
        int result = setsockopt(descriptor, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_BROADCAST, opt);
    }

    // virtual
    bool socket_option_keep_alive::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen);
        check_get_result(get_result, SO_KEEPALIVE, {
            result = true;
            _enabled = (optval != 0);
        });
        return result;
    }

    // virtual
    void socket_option_keep_alive::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = _enabled ? 1 : 0;
        int result = setsockopt(descriptor, SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_KEEPALIVE, opt);
    }

    // virtual
    bool socket_option_do_not_route::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_DONTROUTE, &optval, &optlen);
        check_get_result(get_result, SO_DONTROUTE, {
            result = true;
            _enabled = (optval != 0);
        });
        return result;
    }

    // virtual
    void socket_option_do_not_route::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = _enabled ? 1 : 0;
        int result = setsockopt(descriptor, SOL_SOCKET, SO_DONTROUTE, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_DONTROUTE, opt);
    }

    // virtual
    bool socket_option_reuse_address::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR, &optval, &optlen);
        check_get_result(get_result, SO_REUSEADDR, {
            result = true;
            _enabled = (optval != 0);
        });
        return result;
    }

    // virtual
    void socket_option_reuse_address::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = _enabled ? 1 : 0;
        int result = setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_REUSEADDR, opt);
    }

    // virtual
    bool socket_option_out_of_band_inline::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_OOBINLINE, &optval, &optlen);
        check_get_result(get_result, SO_OOBINLINE, {
            result = true;
            _enabled = (optval != 0);
        });
        return result;
    }

    // virtual
    void socket_option_out_of_band_inline::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = _enabled ? 1 : 0;
        int result = setsockopt(descriptor, SOL_SOCKET, SO_OOBINLINE, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_OOBINLINE, opt);
    }

    // virtual
    bool socket_option_receive_buffer_size::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_RCVBUF, &optval, &optlen);
        check_get_result(get_result, SO_RCVBUF, {
            result = true;
            _size = static_cast<size_t>(optval);
        });
        return result;
    }

    // virtual
    void socket_option_receive_buffer_size::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = static_cast<int>(_size);
        int result = setsockopt(descriptor, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_RCVBUF, opt);
    }

    // virtual
    bool socket_option_send_buffer_size::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_SNDBUF, &optval, &optlen);
        check_get_result(get_result, SO_SNDBUF, {
            result = true;
            _size = static_cast<size_t>(optval);
        });
        return result;
    }

    // virtual
    void socket_option_send_buffer_size::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = static_cast<int>(_size);
        int result = setsockopt(descriptor, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_SNDBUF, opt);
    }

    // virtual
    bool socket_option_receive_low_watermark::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_RCVLOWAT, &optval, &optlen);
        check_get_result(get_result, SO_RCVLOWAT, {
            result = true;
            _size = static_cast<size_t>(optval);
        });
        return result;
    }

    // virtual
    void socket_option_receive_low_watermark::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = static_cast<int>(_size);
        int result = setsockopt(descriptor, SOL_SOCKET, SO_RCVLOWAT, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_RCVLOWAT, opt);
    }

    // virtual
    bool socket_option_send_low_watermark::get(socket::descriptor_type descriptor) noexcept
    {
        bool result { false };
        int optval { -1 };
        socklen_t optlen {sizeof(optval) };
        int get_result = getsockopt(descriptor, SOL_SOCKET, SO_SNDLOWAT, &optval, &optlen);
        check_get_result(get_result, SO_SNDLOWAT, {
            result = true;
            _size = static_cast<size_t>(optval);
        });
        return result;
    }

    // virtual
    void socket_option_send_low_watermark::set(socket::descriptor_type descriptor) const noexcept
    {
        int opt = static_cast<int>(_size);
        int result = setsockopt(descriptor, SOL_SOCKET, SO_SNDLOWAT, reinterpret_cast<char *>(&opt), sizeof(opt));
        check_set_result(result, SO_SNDLOWAT, opt);
    }

}

#undef check_get_result
#undef check_set_result
