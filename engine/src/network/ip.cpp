/**
 * @file ip.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "network/ip.h"

namespace engine {

    /**
     * address_v4
     */

    address_v4::address_v4() :
            _bytes { bytes_t { 0, 0, 0, 0 } }
    {
    }

    address_v4::address_v4(uint_type value) noexcept :
            _bytes { bytes_t { (value >> 24) & 0xFF, (value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF } }
    {
    }

    address_v4::address_v4(const bytes_t& bytes) noexcept :
            _bytes(bytes)
    {
    }

    address_v4::uint_type address_v4::to_uint() const noexcept
    {
        return static_cast<uint_type>(_bytes[0] << 24)  |
                static_cast<uint_type>(_bytes[1] << 16) |
                static_cast<uint_type>(_bytes[2] << 8)  |
                static_cast<uint_type>(_bytes[3]);
    }

    bool address_v4::is_unspecified() const noexcept
    {
        return to_uint() == 0;
    }

    bool address_v4::is_loopback() const noexcept
    {
        return ((to_uint() & 0xFF000000) == 0x7F000000);
    }

    bool address_v4::is_multicast() const noexcept
    {
        return ((to_uint() & 0xF0000000) == 0xE0000000);
    }

    // static
    address_v4 address_v4::any() noexcept
    {
        return address_v4();
    }

    // static
    address_v4 address_v4::loopback() noexcept
    {
        return address_v4(0x7F000001);
    }

    // static
    address_v4 address_v4::broadcast() noexcept
    {
        return address_v4(0xFFFFFFFF);
    }

    /**
     * address_v6
     */

    address_v6::address_v6() :
            _bytes { bytes_t { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
    {
    }

    address_v6::address_v6(const bytes_t& bytes) noexcept :
            _bytes(bytes)
    {
    }

    bool address_v6::is_unspecified() const noexcept
    {
        return false; // @todo
    }

    bool address_v6::is_loopback() const noexcept
    {
        return false; // @todo
    }

    bool address_v6::is_multicast() const noexcept
    {
        return _bytes[0] == 0xFF;
    }

    bool address_v6::is_link_local() const noexcept
    {
        return _bytes[0] == 0xFE && (_bytes[1] & 0xC0) == 0x80;
    }

    bool address_v6::is_site_local() const noexcept
    {
        return _bytes[0] == 0xFE && (_bytes[1] & 0xC0) == 0xC0;
    }

    bool address_v6::is_v4_mapped() const noexcept
    {
        return _bytes[0] == 0 &&
            _bytes[1] == 0 &&
            _bytes[2] == 0 &&
            _bytes[3] == 0 &&
            _bytes[4] == 0 &&
            _bytes[5] == 0 &&
            _bytes[6] == 0 &&
            _bytes[7] == 0 &&
            _bytes[8] == 0 &&
            _bytes[9] == 0 &&
            _bytes[10] == 0xFF &&
            _bytes[11] == 0xFF;
    }

    bool address_v6::is_multicast_node_local() const noexcept
    {
        return is_multicast() && (_bytes[1] & 0x0F) == 0x01;
    }

    bool address_v6::is_multicast_link_local() const noexcept
    {
        return is_multicast() && (_bytes[1] & 0x0F) == 0x02;
    }

    bool address_v6::is_multicast_site_local() const noexcept
    {
        return is_multicast() && (_bytes[1] & 0x0F) == 0x05;
    }

    bool address_v6::is_multicast_org_local() const noexcept
    {
        return is_multicast() && (_bytes[1] & 0x0F) == 0x08;
    }

    bool address_v6::is_multicast_global() const noexcept
    {
        return is_multicast() && (_bytes[1] & 0x0F) == 0x0E;
    }

    /**
     * address
     */

    address::address() :
            _v4 { {} },
            _v6 {}
    {
    }

    address::address(const address_v4& v4) noexcept :
            _v4 { v4 },
            _v6 {}
    {
    }

    address::address(const address_v6& v6) noexcept :
            _v4 {},
            _v6 { v6 }
    {
    }

    bool address::is_unspecified() const noexcept
    {
        bool result { false };
        if (is_v4()) {
            result = _v4->is_unspecified();
        } else if (is_v6()) {
            result = _v6->is_unspecified();
        }
        return result;
    }

    bool address::is_loopback() const noexcept
    {
        bool result { false };
        if (is_v4()) {
            result = _v4->is_loopback();
        } else if (is_v6()) {
            result = _v6->is_loopback();
        }
        return result;
    }

    bool address::is_multicast() const noexcept
    {
        bool result { false };
        if (is_v4()) {
            result = _v4->is_multicast();
        } else if (is_v6()) {
            result = _v6->is_multicast();
        }
        return result;
    }

}
