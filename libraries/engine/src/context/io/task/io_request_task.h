/**
 * @file message_request_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_MESSAGE_REQUEST_TASK_H
#define ENGINE_MESSAGE_REQUEST_TASK_H

#include "task/basic_task.h"
#include "context/io/connection/connection_link.h"

namespace engine {

    /**
     * Incoming message task.
     */
    class io_request_task final : public stl::crucial<basic_task, io_request_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(io_request_task)
        STL_DELETE_ALL_DEFAULT(io_request_task)

        explicit io_request_task(const connection_link& link,
                                 u32 opcode,
                                 const u8 *memory,
                                 size_t length) noexcept;

        virtual ~io_request_task();

        inline const connection_link& link() const noexcept { return _link; }
        inline u32 opcode() const noexcept { return _opcode; }
        inline const u8 *memory() const noexcept { return _memory; }
        inline size_t length() const noexcept { return _length; }

    private:
        connection_link         _link;
        u32                     _opcode;
        u8 *                    _memory;
        size_t                  _length;

    };

}

#endif /* ENGINE_MESSAGE_REQUEST_TASK_H */
