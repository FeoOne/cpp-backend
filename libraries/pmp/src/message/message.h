/**
 * @file message.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMP_MESSAGE_H
#define PMP_MESSAGE_H

#include <stl.h>
#include <engine.h>

namespace pmp {

    class message {
    public:
        STL_DELETE_ALL_DEFAULT(message)

        explicit message(const u8 *memory, size_t size) noexcept : _memory { memory }, _size { size } {}
        virtual ~message() = default;

    protected:
        const u8 *memory() const noexcept { return _memory; }
        size_t size() const noexcept { return _size; }

    private:
        const u8 *      _memory;
        size_t          _size;

    };

    class basic_message_handler {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(basic_message_handler)

        virtual ~basic_message_handler() = default;

        virtual bool handle_message(const engine::connection_link& link,
                                    u32 opcode,
                                    const u8 *memory,
                                    size_t size) noexcept = 0;

    protected:
        basic_message_handler() = default;

    };

}

#endif /* PMP_MESSAGE_H */
