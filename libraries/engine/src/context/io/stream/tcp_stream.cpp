/**
 * @file tcp_read_stream.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "context/io/stream/tcp_stream.h"

namespace engine {

    tcp_stream::tcp_stream(size_t initial_size) noexcept :
            _memory { stl::memory::aligned_alloc<u8>(initial_size) },
            _head { 0 },
            _tail { 0 },
            _size { initial_size }
    {
    }

    tcp_stream::~tcp_stream()
    {
        std::free(_memory);
    }

    void tcp_stream::grow_if_needed() noexcept
    {
        if (available_size() < _size / 4) {
            _size *= 2; // todo: handle unexpected grow, add limit check
            _memory = stl::memory::realloc<u8>(_memory, _size);
        }
    }

    void tcp_stream::flush_if_needed() noexcept
    {
        if (_head == _tail) {
            _head = 0;
            _tail = 0;
        }
    }

}
