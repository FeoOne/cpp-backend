/**
 * @file tcp_read_stream.h
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#ifndef ENGINE_IO_STREAM_H
#define ENGINE_IO_STREAM_H

#include <stl.h>

namespace engine {

    class tcp_read_stream final {
    public:
        STL_DECLARE_SMARTPOINTERS(tcp_read_stream)
        STL_DELETE_ALL_DEFAULT(tcp_read_stream)

        explicit tcp_read_stream(size_t initial_size) noexcept;
        ~tcp_read_stream();

        u8 *head() noexcept { return &_memory[_head]; }
        u8 *tail() noexcept { return &_memory[_tail]; }

        void increase_head(size_t inc) noexcept { _head += inc; }
        void increase_tail(size_t inc) noexcept { _tail += inc; }

        size_t available_size() const noexcept { return _size - _tail; }
        size_t useful_size() const noexcept { return _tail - _head; }

    private:
        u8                      _memory;
        size_t                  _head;
        size_t                  _tail;
        size_t                  _size;

    };

}

#endif /* ENGINE_IO_STREAM_H */
