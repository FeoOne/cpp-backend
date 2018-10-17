/**
 * @file pmp.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMP_PMP_H
#define PMP_PMP_H

#include "message/message.h"
#include "message/message_builder.h"

namespace pmp {

    struct session_id {
        static constexpr size_t backend { 1 };
        static constexpr size_t database { 2 };

        static constexpr size_t max_count { 32 };

    };

}

#endif /* PMP_PMP_H */
