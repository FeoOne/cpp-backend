//
// Created by Feo on 12/10/2018.
//

#ifndef PMGEN_DATABASE_MESSAGE_HANDLER_H
#define PMGEN_DATABASE_MESSAGE_HANDLER_H

#include "backend_database_message_gen.h"
#include "backend_database_handler_gen.h"

namespace backend {

    class database_message_handler final : public pmp::backend_database::message_handler {
    public:
        STL_DECLARE_SMARTPOINTERS(database_message_handler)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(database_message_handler)

        database_message_handler() = default;
        virtual ~database_message_handler() = default;

    private:
        void handle_handshake_request(pmp::backend_database::handshake_request::uptr&& message) noexcept final;
        void handle_handshake_response(pmp::backend_database::handshake_response::uptr&& message) noexcept final;

    };

}

#endif /* PMGEN_DATABASE_MESSAGE_HANDLER_H */
