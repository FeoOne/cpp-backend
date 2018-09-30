/**
 * @file message.cpp
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#include "message/message.h"

namespace engine {

    bool message_header::is_magic_correct() const noexcept
    {
        static constexpr u32 hex { 0x31337fe0 };
        return magic() == hex;
    }

}
