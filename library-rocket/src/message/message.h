/**
 * @file message.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef ROCKET_MESSAGE_H
#define ROCKET_MESSAGE_H

#include <groot.h>

namespace rocket {

    class message_header final {
    public:
        GR_DELETE_ALL_DEFAULT(message_header)

        explicit message_header(u8 *memory) noexcept : _memory { memory } {}
        ~message_header() = default;

        u32 magic() const noexcept { return *reinterpret_cast<u32 *>(&_memory[MAGIC_OFFSET]); }
        u32 opcode() const noexcept { return *reinterpret_cast<u32 *>(&_memory[OPCODE_OFFSET]); }
        u32 version() const noexcept { return *reinterpret_cast<u32 *>(&_memory[VERSION_OFFSET]); }
        u32 crc() const noexcept { return *reinterpret_cast<u32 *>(&_memory[CRC_OFFSET]); }

        void magic(u32 value) noexcept { std::memcpy(&_memory[MAGIC_OFFSET], &value, sizeof(value)); }
        void opcode(u32 value) noexcept { std::memcpy(&_memory[OPCODE_OFFSET], &value, sizeof(value)); }
        void version(u32 value) noexcept { std::memcpy(&_memory[VERSION_OFFSET], &value, sizeof(value)); }
        void crc(u32 value) noexcept { std::memcpy(&_memory[CRC_OFFSET], &value, sizeof(value)); }

    private:
        static constexpr size_t MAGIC_OFFSET { 0 };
        static constexpr size_t OPCODE_OFFSET { 4 };
        static constexpr size_t VERSION_OFFSET { 8 };
        static constexpr size_t CRC_OFFSET { 12 };

        u8 *    _memory;

    };

    class message {
    public:
        message();
        ~message();

    private:

    };

}

#endif /* ROCKET_MESSAGE_H */
