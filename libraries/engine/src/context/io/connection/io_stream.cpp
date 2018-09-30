/**
 * @file io_stream.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "context/io/connection/io_stream.h"

namespace engine {

    io_stream::io_stream(size_t initial_size) noexcept :
            _memory { stl::memory::malloc<u8>(initial_size) },
            _head { 0 },
            _tail { 0 },
            _size { initial_size }
    {
    }

    io_stream::~io_stream() {
        stl::memory::free(_memory);
    }

    void io_stream::grow_if_needed() noexcept
    {
        if (free_size() >= _size - _size / 10) {
            _size *= 2;
            _memory = reinterpret_cast<u8 *>(je_realloc(_memory, _size));
        }
    }

    void io_stream::flush_if_needed() noexcept
    {
        if (_head == _tail) {
            _head = 0;
            _tail = 0;
        }
    }

}
