/**
 * @file checksum.h
 * @author Feo
 * @date 24/08/2018
 * @brief
 */

#ifndef STL_CHECKSUM_H
#define STL_CHECKSUM_H

#include "scalar/numeric.h"

namespace stl {

    class checksum {
    public:
        /**
         * CRC-CCITT crc16
         * @param buffer Data.
         * @param size Data size.
         * @return CRC16 result.
         */
        static u16 crc16(u8 *buffer, size_t size) noexcept;
        static u32 crc32(const u8 *buffer, size_t size) noexcept;

    private:

    };

}

#endif /* STL_CHECKSUM_H */
