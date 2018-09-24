/**
 * @file connection_context.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef ROCKET_CONNECTION_CONTEXT_H
#define ROCKET_CONNECTION_CONTEXT_H

#include <groot.h>

#define RC_READ_BUFFER_INITIAL_SIZE 4096

namespace rocket {

    /**
     *
     */
    class read_buffer final {
    public:
        GR_DECLARE_SMARTPOINTERS(read_buffer)

        read_buffer() :
            _memory { reinterpret_cast<u8 *>(std::malloc(RC_READ_BUFFER_INITIAL_SIZE)) },
            _head { 0 },
            _tail { 0 },
            _size { RC_READ_BUFFER_INITIAL_SIZE }
        {
        }

        ~read_buffer() {
            std::free(_memory);
        }

    private:
        u8 *                    _memory;
        size_t                  _head;
        size_t                  _tail;
        size_t                  _size;

    };

    /**
     *
     */
    class write_buffer {
    public:
        GR_DECLARE_SMARTPOINTERS(write_buffer)

    };

    /**
     *
     */
    class connection_context final {
    public:

    private:
        read_buffer::uptr       _read_buffer;
        write_buffer::uptr      _write_buffer;

    };

}

#endif /* ROCKET_CONNECTION_CONTEXT_H */
