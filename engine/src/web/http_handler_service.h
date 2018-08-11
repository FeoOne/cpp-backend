/**
 * @file http_handler_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_HANDLER_SERVICE_H
#define ENGINE_HTTP_HANDLER_SERVICE_H

#include "core/execution_service.h"

namespace engine {

    class http_handler_service : public execution_service {
    public:
        http_handler_service();
        virtual ~http_handler_service();

    private:

    };

}

#endif /* ENGINE_HTTP_HANDLER_SERVICE_H */
