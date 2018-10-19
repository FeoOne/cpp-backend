/**
 * @file io_response_task.cpp
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#include "context/io/task/io_response_task.h"

namespace engine {

    io_response_task::io_response_task(const connection_link& link,
                                       u32 opcode,
                                       u8 *memory,
                                       size_t length,
                                       bool is_urgent) noexcept :
            _link { link },
            _opcode { opcode },
            _memory { memory },
            _length { length },
            _is_urgent { is_urgent }
    {
        // memory allocated by message builder
    }

    io_response_task::~io_response_task()
    {
        if (_memory != nullptr) {
            stl::memory::free(_memory);
        }
    }

}
