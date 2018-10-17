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

    struct consts {
        static constexpr size_t backend_id { 1 };
        static constexpr size_t database_id { 2 };

    };

}

#endif /* PMP_PMP_H */
