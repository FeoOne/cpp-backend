/**
 * @file message_response_task.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef ENGINE_MESSAGE_RESPONSE_TASK_H
#define ENGINE_MESSAGE_RESPONSE_TASK_H

#include "task/basic_task.h"
#include "context/io/connection/connection_link.h"

namespace engine {

    /**
     * Outgoing message task.
     */
    class io_response_task final : public stl::crucial<basic_task, io_response_task> {
    public:
        STL_DECLARE_SMARTPOINTERS(io_response_task)
        STL_DELETE_ALL_DEFAULT(io_response_task)

        explicit io_response_task(const connection_link& link,
                                  u32 opcode,
                                  u8 *memory,
                                  size_t length,
                                  bool is_urgent) noexcept;

        virtual ~io_response_task();

        inline const connection_link& link() const noexcept { return _link; }
        inline u32 opcode() const noexcept { return _opcode; }
        inline const u8 *memory() const noexcept { return _memory; }
        inline size_t length() const noexcept { return _length; }
        inline bool is_urgent() const noexcept { return _is_urgent; }

    private:
        connection_link         _link;
        u32                     _opcode;
        u8 *                    _memory;
        size_t                  _length;
        bool                    _is_urgent;

    };

}

#endif /* ENGINE_MESSAGE_RESPONSE_TASK_H */
