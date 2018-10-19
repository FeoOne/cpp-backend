/**
 * @file tcp_write_stream.h
 * @author Feo
 * @date 19/10/2018
 * @brief
 */

#ifndef ENGINE_TCP_WRITE_STREAM_H
#define ENGINE_TCP_WRITE_STREAM_H

#include <stl.h>

namespace engine {

    class tcp_write_stream final {
    public:
        STL_DECLARE_SMARTPOINTERS(tcp_write_stream)
        STL_DELETE_ALL_DEFAULT(tcp_write_stream)

        explicit tcp_write_stream(size_t initial_size) noexcept;
        ~tcp_write_stream();

        u8 *head() noexcept { return &_memory[_head]; }
        u8 *tail() noexcept { return &_memory[_tail]; }

        void increase_head(size_t inc) noexcept { _head += inc; }
        void increase_tail(size_t inc) noexcept { _tail += inc; }

        size_t available_size() const noexcept { return _size - _tail; }
        size_t useful_size() const noexcept { return _tail - _head; }

        void grow_if_needed() noexcept;
        void flush_if_needed() noexcept;

    private:
        u8 *                    _memory;
        size_t                  _head;
        size_t                  _tail;
        size_t                  _size;

    };

}

#endif /* ENGINE_TCP_WRITE_STREAM_H */
