/**
 * @file web_server_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_SERVER_SERVICE_H
#define ENGINE_WEB_SERVER_SERVICE_H

#include "core/execution_service.h"

namespace engine {

    class web_server_service : public execution_service {
    public:
        FW_DECLARE_SMARTPOINTERS(web_server_service)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(web_server_service)

        web_server_service();
        virtual ~web_server_service();

        void create() noexcept final;
        void destroy() noexcept final;

    private:

    };

}

#endif /* ENGINE_WEB_SERVER_SERVICE_H */
