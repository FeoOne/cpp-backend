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

    /**
     *
     */
    class message_header final {
    public:
        GR_DELETE_ALL_DEFAULT(message_header)

        static constexpr size_t SIZE { 20 };

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

    /**
     *
     */
    class message {
    public:
        using opcode_type = u32;

        explicit message(nullptr_t) noexcept {}
        virtual ~message() {}

    private:

    };

    /**
     *
     */
    class dummy1_message final : public message {
    public:
        static constexpr opcode_type OPCODE { 1 };

        dummy1_message() : message(nullptr) {}
        virtual ~dummy1_message() {}

    };

    class dummy2_message final : public message {
    public:
        static constexpr opcode_type OPCODE { 2 };

        dummy2_message() : message(nullptr) {}
        virtual ~dummy2_message() {}

    };



    template<size_t T>
    class message_deserializer {
        message *deserialize(u8 *, size_t) noexcept { return nullptr; }
    };

    template<>
    class message_deserializer<dummy1_message::OPCODE> {
        message *deserialize(u8 *, size_t) noexcept { return new (std::nothrow) dummy1_message; }
    };

    template<>
    class message_deserializer<dummy2_message::OPCODE> {
        message *deserialize(u8 *, size_t) noexcept { return new (std::nothrow) dummy2_message; }
    };
}

#endif /* ROCKET_MESSAGE_H */
