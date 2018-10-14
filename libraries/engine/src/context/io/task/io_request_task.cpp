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
                                     const u8 *memory,
                                     size_t length) noexcept :
            _link { link },
            _opcode { opcode },
            _memory { memory },
            _length { length }
    {
    }

}
