/**
 * @file io_stream.h
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#ifndef ROCKET_IO_STREAM_H
#define ROCKET_IO_STREAM_H

#include <groot.h>

namespace rocket {

    class io_stream {
    public:
        GR_DELETE_ALL_DEFAULT(io_stream)

        explicit io_stream(size_t initial_size) noexcept;
        ~io_stream();

        u8 *head() noexcept { return &_memory[_head]; }
        u8 *tail() noexcept { return &_memory[_tail]; }

        void increase_head(size_t inc) noexcept { _head += inc; }
        void increase_tail(size_t inc) noexcept { _tail += inc; }

        size_t used_size() const noexcept { return _tail - _head; }
        size_t free_size() const noexcept { return _size - _tail; }

        void grow_if_needed() noexcept;
        void flush_if_needed() noexcept;

    private:
        u8 *                    _memory;
        size_t                  _head;
        size_t                  _tail;
        size_t                  _size;

    };

}

#endif /* ROCKET_IO_STREAM_H */
