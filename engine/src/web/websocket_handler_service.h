/**
 * @file websocket_handler_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_WEBSOCKET_HANDLER_SERVICE_H
#define ENGINE_WEBSOCKET_HANDLER_SERVICE_H

#include "core/execution_service.h"

namespace engine {

    class websocket_handler_service : public execution_service {
    public:
        websocket_handler_service();
        virtual ~websocket_handler_service();

    private:

    };

}

#endif /* ENGINE_WEBSOCKET_HANDLER_SERVICE_H */
