/**
 * @file input_stream.h
 * @author Feo
 * @date 24/08/2018
 * @brief
 */

#ifndef ROCKET_INPUT_STREAM_H
#define ROCKET_INPUT_STREAM_H

#include <groot.h>

#include "main/rocket_consts.h"

namespace rocket {

    class input_stream {
    public:
        GR_DECLARE_SMARTPOINTERS(input_stream)
        GR_DELETE_ALL_DEFAULT(input_stream)

        explicit input_stream(size_t initial_size) noexcept;
        ~input_stream();

        u8 *data() noexcept { return &_buffer[_offset]; }
        size_t size() const noexcept { return _tail - _offset; }
        void shift(size_t size) noexcept;

    private:
        u8 *            _buffer;
        size_t          _size;
        size_t          _offset;
        size_t          _tail;

    };

}

#endif /* ROCKET_INPUT_STREAM_H */
