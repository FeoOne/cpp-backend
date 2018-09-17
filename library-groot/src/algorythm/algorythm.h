/**
 * @file algorythm.h
 * @author Feo
 * @date 24/08/2018
 * @brief
 */

#ifndef GROOT_ALGORYTHM_H
#define GROOT_ALGORYTHM_H

#include "scalar/numeric.h"

namespace groot {

    class algorythm {
    public:
        /**
         * CRC-CCITT crc16
         * @param buffer Data.
         * @param size Data size.
         * @return CRC16 result.
         */
        static u16 crc16(u8 *buffer, size_t size) noexcept;

    private:

    };

}

#endif /* GROOT_ALGORYTHM_H */
