/**
 * @file pending_invoice.cpp
 * @author Feo
 * @date 14/11/2018
 * @brief
 */

#include "logic/invoice/pending_invoice.h"

namespace backend {

    pending_invoice::pending_invoice(const stl::uuid& merchandise_guid, std::string&& mail) noexcept :
            _state { pending_state::created },
            _guid { stl::uuid::generate_strategy::RANDOM },
            _merchandise_guid { merchandise_guid },
            _mail { mail },
            _cy {},
            _amount { 0 }
    {

    }

}
