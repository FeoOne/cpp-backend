/**
 * @file message_request_task.cpp
 * @author Feo
 * @date 25/09/2018
 * @brief
 */

#include "io/task/message_request_task.h"

namespace rocket {

    message_request_task::message_request_task(const connection_link& source,
                                               message::opcode_type opcode,
                                               u8 *memory,
                                               size_t length) noexcept :
            _source { source },
            _opcode { opcode },
            _memory { nullptr },
            _length { length }
    {
        if (length > 0) {
            _memory = groot::memory::aligned_alloc<u8>(length);
            if (_memory != nullptr) {
                _memory = reinterpret_cast<u8 *>(std::memcpy(_memory, memory, length));
            }
        }
    }

    // virtual
    message_request_task::~message_request_task()
    {
        if (_memory != nullptr) {
            groot::memory::free(_memory);
        }
    }

}
