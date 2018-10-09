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
        explicit message(const u8 *memory, size_t size) noexcept : _memory { memory }, _size { size } {}
        virtual ~message() = default;

    protected:
        const u8 *memory() const noexcept { return _memory; }
        size_t size() const noexcept { return _size; }

    private:
        const u8 *      _memory;
        size_t          _size;

    };

}

#endif /* PMP_MESSAGE_H */
