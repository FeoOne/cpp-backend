//
// Created by Feo on 15/10/2018.
//

#ifndef PMP_MESSAGE_BUILDER_H
#define PMP_MESSAGE_BUILDER_H

#include "message/message.h"

namespace pmp {

    class message_builder {
    public:
        STL_DECLARE_SMARTPOINTERS(message_builder)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(message_builder)

        virtual ~message_builder() = default;

        virtual void build(u8 **memptr, size_t *length) const noexcept = 0;

    protected:
        message_builder() = default;

        static void copy(u8 *memory, const char *string) noexcept;
        static void copy(u8 *memory, u8 value) noexcept;
        static void copy(u8 *memory, s8 value) noexcept;
        static void copy(u8 *memory, u16 value) noexcept;
        static void copy(u8 *memory, s16 value) noexcept;
        static void copy(u8 *memory, u32 value) noexcept;
        static void copy(u8 *memory, s32 value) noexcept;
        static void copy(u8 *memory, u64 value) noexcept;
        static void copy(u8 *memory, s64 value) noexcept;

    };

}

#endif /* PMP_MESSAGE_BUILDER_H */
