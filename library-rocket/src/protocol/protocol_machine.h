/**
 * @file protocol.h
 * @author Feo
 * @date 24/08/2018
 * @brief
 */

#ifndef ROCKET_PROTOCOL_H
#define ROCKET_PROTOCOL_H

#include <groot.h>

namespace rocket {

    struct packet_header {
    private:
        u32     _magic;
        u32     _version;
        u32     _length;
        u16     _opcode;
        u16     _crc16;

    public:
        u32 get_magic() const noexcept { return ntohl(_magic); }
        u32 get_version() const noexcept { return ntohl(_version); }
        u32 get_length() const noexcept { return ntohl(_length); }
        u16 get_opcode() const noexcept { return ntohs(_opcode); }
        u16 get_crc16() const noexcept { return ntohs(_crc16); }

    };

    class protocol_machine {
    public:
        protocol_machine() {  }
        ~protocol_machine();

    private:

    };

}

#endif /* ROCKET_PROTOCOL_H */
