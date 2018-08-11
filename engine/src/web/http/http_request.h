/**
 * @file http_request.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_REQUEST_H
#define ENGINE_HTTP_REQUEST_H

#include <framework.h>

namespace engine {

    class http_request {
    public:
        FW_DECLARE_SMARTPOINTERS(http_request)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_request)

        http_request();
        ~http_request();

    private:

    };

}

#endif /* ENGINE_HTTP_REQUEST_H */
