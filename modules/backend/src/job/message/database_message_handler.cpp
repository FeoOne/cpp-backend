//
// Created by Feo on 12/10/2018.
//

#include "job/message/database_message_handler.h"

namespace backend {

    // virtual
    void database_message_handler::handle_handshake_request(
            pmp::backend_database::handshake_request::uptr &&message) noexcept
    {

    }

    // virtual
    void database_message_handler::handle_handshake_response(
            pmp::backend_database::handshake_response::uptr &&message) noexcept
    {

    }

}
