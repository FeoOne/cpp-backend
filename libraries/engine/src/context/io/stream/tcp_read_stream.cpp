/**
 * @file tcp_read_stream.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "context/io/stream/tcp_read_stream.h"

namespace engine {

    tcp_read_stream::tcp_read_stream(size_t initial_size) noexcept :
            _memory {},
            _head { 0 },
            _tail { 0 },
            _size { initial_size }
    {
    }

    tcp_read_stream::~tcp_read_stream()
    {
    }

    void tcp_read_stream::start_over() noexcept
    {
        auto data_size { raw_data_size() };

        if (data_size != 0) {
            // todo: handle overlapping
            logassert(data_size <= _head, "fixme");
            std::memcpy(_memory, head(), data_size);
        }

        _head = 0;
        _tail = data_size;
    }

}
