/**
 * @file database_messaging_service.cpp
 * @author Feo
 * @date 12/10/2018
 * @brief
 */

#include "job/service/message/database_messaging_service.h"

namespace backend {

    database_messaging_service::database_messaging_service(const stl::setting& config,
                                                           engine::task_router *router,
                                                           const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate)
    {
    }

    // virtual
    void database_messaging_service::setup() noexcept
    {

    }

    // virtual
    void database_messaging_service::reset() noexcept
    {

    }

    // virtual
    void database_messaging_service::handle_handshake_request(const engine::connection_link& link,
            pmp::backend_database::handshake_request::uptr&& message) noexcept
    {
        // todo: verify version

        stl::md5_hash::uptr md5 { stl::md5_hash::make_unique() };
        md5->update(message->get_phrase());
        md5->finalize();

        pmp::backend_database::handshake_response_builder builder;
        builder.set_cipher(md5->digest());

        u8 *memory { nullptr };
        size_t length { 0 };
        builder.build(&memory, &length);

        auto task {
                engine::basic_task::create<engine::io_response_task>(link,
                                                                     pmp::backend_database::handshake_response::opcode,
                                                                     memory,
                                                                     length,
                                                                     true)
        };
        router()->enqueue(task);
    }

    // virtual
    void database_messaging_service::handle_handshake_response(const engine::connection_link& link,
            pmp::backend_database::handshake_response::uptr&& message) noexcept
    {
        // nothing there
    }

}
