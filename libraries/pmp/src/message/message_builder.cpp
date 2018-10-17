//
// Created by Feo on 15/10/2018.
//

#include "message/message_builder.h"

namespace pmp {

    // static
    void message_builder::copy(u8 *memory, const char *string) noexcept
    {
        std::memcpy(memory, string, std::strlen(string) + 1);
    }

    // static
    void message_builder::copy(u8 *memory, u8 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(u8));
    }

    // static
    void message_builder::copy(u8 *memory, s8 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(s8));
    }

    // static
    void message_builder::copy(u8 *memory, u16 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(u16));
    }

    // static
    void message_builder::copy(u8 *memory, s16 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(s16));
    }

    // static
    void message_builder::copy(u8 *memory, u32 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(u32));
    }

    // static
    void message_builder::copy(u8 *memory, s32 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(s32));
    }

    // static
    void message_builder::copy(u8 *memory, u64 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(u64));
    }

    // static
    void message_builder::copy(u8 *memory, s64 value) noexcept
    {
        std::memcpy(memory, &value, sizeof(s64));
    }

}
