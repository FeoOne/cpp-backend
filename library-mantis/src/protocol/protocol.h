/**
 * @file protocol.h
 * @author Feo
 * @date 24/08/2018
 * @brief
 */

#ifndef MANTIS_PROTOCOL_H
#define MANTIS_PROTOCOL_H

#include <cstdint>

namespace mantis {

    class network_error {
    public:
        static constexpr uint32_t CREATE_INVOICE_INTERNAL_ERROR { 10000 };

    };

}


#endif /* PROJECT_PROTOCOL_H */
