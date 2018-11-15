/**
 * @file pending_invoice.cpp
 * @author Feo
 * @date 14/11/2018
 * @brief
 */



#include "logic/invoice/pending_invoice.h"

namespace backend {

    pending_invoice::pending_invoice(const stl::uuid& merchandise_guid, std::string&& mail, u64 amount) noexcept :
            _state { pending_state::initialized },
            _id { 0 },
            _guid {},
            _wallet_guid {},
            _confirm_block_count { 0 },
            _callback_url { nullptr },
            _merchandise_guid { merchandise_guid },
            _mail { mail },
            _amount { 0 }
    {
        generate_address();
    }

    pending_invoice::~pending_invoice()
    {
        if (_callback_url != nullptr) {
            std::free(_callback_url);
        }
    }

    void pending_invoice::generate_address() noexcept
    {

    }

    void pending_invoice::update(create_float_invoice_db_request *request) noexcept
    {
        _id = request->invoice_id;
        _guid = request->invoice_guid;
        _wallet_guid = request->wallet_guid;
        _confirm_block_count = request->confirm_block_count;
        _callback_url = request->callback_url;

        _state = pending_state::created;
    }

}
