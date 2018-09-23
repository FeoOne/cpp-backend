/**
 * @file output_buffer.h
 * @author Feo
 * @date 22/09/2018
 * @brief
 */

#ifndef ROCKET_OUTPUT_BUFFER_H
#define ROCKET_OUTPUT_BUFFER_H

#include <groot.h>

#include "main/rocket_consts.h"

namespace rocket {

    class output_buffer {
    public:
        GR_DECLARE_SMARTPOINTERS(output_buffer)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(output_buffer)

        output_buffer() :
                _head { 0 },
                _tail { 0 }
        {
#ifndef NDEBUG
            std::memset(_memory, 0, SIZE);
#endif
        }

        ~output_buffer() = default;

        size_t size() const noexcept { return SIZE; }

    private:
        static constexpr size_t SIZE { RC_IO_BUFFER_SIZE };

        u8              _memory[SIZE];
        size_t          _head;
        size_t          _tail;

    };

}

#endif /* ROCKET_OUTPUT_BUFFER_H */
