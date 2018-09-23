/**
 * @file input_buffer.h
 * @author Feo
 * @date 22/09/2018
 * @brief
 */

#ifndef ROCKET_INPUT_BUFFER_H
#define ROCKET_INPUT_BUFFER_H

#include <groot.h>

#include "main/rocket_consts.h"

namespace rocket {

    /**
     * read/recv buffer
     */
    class input_buffer {
    public:
        GR_DECLARE_SMARTPOINTERS(input_buffer)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(input_buffer)

        input_buffer() :
                _memory {},
                _head { 0 },
                _tail { 0 }
        {
#ifndef NDEBUG
            _memory.fill(0);
#endif
        }

        ~input_buffer() = default;

        size_t size() const noexcept { return SIZE; }
        size_t available_size() const noexcept { return SIZE - _tail; }

    private:
        static constexpr size_t SIZE { RC_IO_BUFFER_SIZE };

        std::array<u8, SIZE>    _memory;
        size_t                  _head;
        size_t                  _tail;

    };

}

#endif /* ROCKET_INPUT_BUFFER_H */
