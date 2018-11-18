/**
 * @file pending_invoice.cpp
 * @author Feo
 * @date 14/11/2018
 * @brief
 */

#include "bitcoin/bitcoin.h"

#include "logic/invoice/pending_invoice.h"

namespace backend {

    pending_invoice::pending_invoice(const stl::uuid& merchandise_guid,
                                     std::string&& mail,
                                     s64 amount,
                                     s64 fee) noexcept :
            _state { pending_state::initialized },
            _id { 0 },
            _guid {},
            _pending_guid { stl::uuid::generate_strategy::RANDOM },
            _wallet_guid {},
            _confirm_block_count { 0 },
            _callback_url {},
            _merchandise_guid { merchandise_guid },
            _mail { mail },
            _amount { amount },
            _fee { fee },
            _connection { nullptr }
    {
    }

    pending_invoice::~pending_invoice()
    {
    }

    void pending_invoice::update(create_float_invoice_db_request *request) noexcept
    {
        _id = request->invoice_id;
        _guid = request->invoice_guid;
        _wallet_guid = request->wallet_guid;
        _confirm_block_count = request->confirm_block_count;
        _callback_url.assign(request->callback_url);

        _address = bitcoin::generate_address(_wallet_guid.data(), stl::uuid::size, _id);

        _state = pending_state::created;
    }

}
