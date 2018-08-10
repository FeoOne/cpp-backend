/**
 * @file ip.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_IP_H
#define ENGINE_IP_H

#include <framework.h>
#include <netinet/in.h>

namespace engine {

    /**
     *
     */
    class address_v4 {
    public:
        using uint_type = uint_least32_t;

        class bytes_t : public std::array<u8, 4> {
        public:
            template<typename... T>
            explicit constexpr bytes_t(T... args) :
                    std::array<u8, 4> { { static_cast<u8>(args)... } } {}
        };

        address_v4();
        explicit address_v4(uint_type value) noexcept;
        explicit address_v4(const bytes_t& bytes) noexcept;

        uint_type to_uint() const noexcept;

        bytes_t to_bytes() const noexcept { return _bytes; }

        bool is_unspecified() const noexcept;
        bool is_loopback() const noexcept;
        bool is_multicast() const noexcept;

        static address_v4 any() noexcept;
        static address_v4 loopback() noexcept;
        static address_v4 broadcast() noexcept;

    private:
        bytes_t         _bytes;

    };

    /**
     *
     */
    class address_v6 {
    public:
        class bytes_t : public std::array<u8, 16> {
        public:
            template<typename... T>
            explicit constexpr bytes_t(T... args) :
                    std::array<u8, 16> { { static_cast<u8>(args)... } } {}
        };

        address_v6();
        explicit address_v6(const bytes_t& bytes) noexcept;

        bytes_t to_bytes() const noexcept { return _bytes; }

        bool is_unspecified() const noexcept;
        bool is_loopback() const noexcept;
        bool is_multicast() const noexcept;
        bool is_link_local() const noexcept;
        bool is_site_local() const noexcept;
        bool is_v4_mapped() const noexcept;
        bool is_multicast_node_local() const noexcept;
        bool is_multicast_link_local() const noexcept;
        bool is_multicast_site_local() const noexcept;
        bool is_multicast_org_local() const noexcept;
        bool is_multicast_global() const noexcept;

    private:
        bytes_t         _bytes;

    };

    /**
     *
     */
    class address {
    public:
        address();
        explicit address(const address_v4& v4) noexcept;
        explicit address(const address_v6& v6) noexcept;
        virtual ~address() = default;

        bool is_unspecified() const noexcept;
        bool is_loopback() const noexcept;
        bool is_multicast() const noexcept;

        bool is_v4() const noexcept { return static_cast<bool>(_v4); }
        bool is_v6() const noexcept { return static_cast<bool>(_v6); }

    private:
        std::experimental::optional<address_v4>     _v4;
        std::experimental::optional<address_v6>     _v6;

    };

    /**
     *
     */
    class endpoint {
    public:
        using port_type = u16;

        endpoint() :
                _addr {},
                _port { 0 }
        {}

        explicit endpoint(const address& addr, port_type port) noexcept :
                _addr { addr },
                _port { port }
        {}

        address addr() const noexcept { return _addr; }
        void addr(const address& addr) noexcept { _addr = addr; }

        port_type port() const noexcept { return _port; }
        void port(port_type port) noexcept { _port = port; }

    private:
        union sock_addr {
            sockaddr_in     v4;
            sockaddr_in6    v6;
        };

        address             _addr;
        port_type           _port;

    };

}

#endif /* ENGINE_IP_H */
