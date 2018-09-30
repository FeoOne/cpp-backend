/**
 * @file message_request_task.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "context/io/task/io_request_task.h"

namespace engine {

    io_request_task::io_request_task(const connection_link& link,
                                     message::opcode_type opcode,
                                     u8 *memory,
                                     size_t length) noexcept :
            _link { link },
            _opcode { opcode },
            _memory { nullptr },
            _length { length }
    {
        if (length > 0) {
            _memory = stl::memory::aligned_alloc<u8>(length);
            if (_memory != nullptr) {
                _memory = reinterpret_cast<u8 *>(std::memcpy(_memory, memory, length));
            }
        }
    }

    // virtual
    io_request_task::~io_request_task()
    {
        if (_memory != nullptr) {
            stl::memory::free(_memory);
        }
    }

}
