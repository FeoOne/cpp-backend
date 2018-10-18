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

        static void copy_raw(u8 *dst, const void *src, size_t size) noexcept;

        template<typename T, typename = typename std::enable_if<std::is_integral_v<T>>::type>
        static void copy(u8 *memory, T value) noexcept {
            copy_raw(memory, &value, sizeof(T));
        }

        template<typename T, typename = typename std::enable_if<std::is_integral_v<T>>::type>
        static void copy(u8 *memory, const T *values, size_t count) noexcept {
            copy_raw(memory, values, sizeof(T) * count);
        }

        static void copy(u8 *memory, const char *string) noexcept {
            copy_raw(memory, string, std::strlen(string) + 1);
        }

    };

}

#endif /* PMP_MESSAGE_BUILDER_H */
