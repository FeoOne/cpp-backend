/**
 * @file message.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMP_MESSAGE_H
#define PMP_MESSAGE_H

#include <stl.h>

namespace pmp {

    class message {
    public:
        explicit message(u8 *memory, size_t size) noexcept : _memory { memory }, _size { size } {}
        virtual ~message() = default;

    protected:
        const u8 *memory() const noexcept { return _memory; }
        size_t size() const noexcept { return _size; }

    private:
        u8 *            _memory;
        size_t          _size;

    };

    class handshake_message : public message {
    public:
        explicit handshake_message(u8 *memory, size_t size) noexcept : message(memory, size) {}

        const char *get_text() const noexcept { return reinterpret_cast<const char *>(memory()[text_offset()]); }
        u16 get_version() const noexcept { return *reinterpret_cast<u16 *>(memory()[version_offset()]); }

    private:
        size_t text_offset() const noexcept { return 0; }
        size_t text_length() const noexcept { return std::strlen(get_text()) + 1; }

        size_t version_offset() const noexcept { return text_offset() + text_length(); }
        size_t version_length() const noexcept { return sizeof(u16); }

    };

}

#endif /* PMP_MESSAGE_H */
