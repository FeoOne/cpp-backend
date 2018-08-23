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

    struct protocol_header {
        u32     magic;
        u32     opcode;
        u32     length;
        u16     version;
        u16     reserved;
    };

    class protocol_machine {
    public:
        protocol_machine();
        ~protocol_machine();

    private:

    };

}

#endif /* ROCKET_PROTOCOL_H */
