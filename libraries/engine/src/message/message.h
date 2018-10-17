/**
 * @file message.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H

#include <stl.h>

namespace engine {

    /**
     *
     */
    class message_header final {
    public:
        STL_DELETE_ALL_DEFAULT(message_header)

        static constexpr size_t size { 20 };

        explicit message_header(u8 *memory) noexcept : _memory { memory } {}
        ~message_header() = default;

        u32 magic() const noexcept { return *reinterpret_cast<u32 *>(&_memory[MAGIC_OFFSET]); }
        u32 opcode() const noexcept { return *reinterpret_cast<u32 *>(&_memory[OPCODE_OFFSET]); }
        u32 version() const noexcept { return *reinterpret_cast<u32 *>(&_memory[VERSION_OFFSET]); }
        u32 length() const noexcept { return *reinterpret_cast<u16 *>(&_memory[LENGTH_OFFSET]); }
        u32 crc32() const noexcept { return *reinterpret_cast<u16 *>(&_memory[CRC32_OFFSET]); }

        void magic(u32 value) noexcept { std::memcpy(&_memory[MAGIC_OFFSET], &value, sizeof(value)); }
        void opcode(u32 value) noexcept { std::memcpy(&_memory[OPCODE_OFFSET], &value, sizeof(value)); }
        void version(u32 value) noexcept { std::memcpy(&_memory[VERSION_OFFSET], &value, sizeof(value)); }
        void length(u32 value) noexcept { std::memcpy(&_memory[LENGTH_OFFSET], &value, sizeof(value)); }
        void crc32(u32 value) noexcept { std::memcpy(&_memory[CRC32_OFFSET], &value, sizeof(value)); }

        bool is_magic_correct() const noexcept;

    private:
        static constexpr size_t MAGIC_OFFSET { 0 };
        static constexpr size_t OPCODE_OFFSET { 4 };
        static constexpr size_t VERSION_OFFSET { 8 };
        static constexpr size_t LENGTH_OFFSET { 12 };
        static constexpr size_t CRC32_OFFSET { 16 };

        u8 *    _memory;

    };

}

#endif /* ENGINE_MESSAGE_H */
