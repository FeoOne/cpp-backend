//
// Created by Feo on 15/10/2018.
//

#include "message/message_builder.h"

namespace pmp {

    //static
    void message_builder::copy_raw(u8 *dst, const void *src, size_t size) noexcept
    {
        std::memcpy(dst, src, size);
    }

}
