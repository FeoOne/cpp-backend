/**
 * @file http_response.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef ENGINE_HTTP_RESPONSE_H
#define ENGINE_HTTP_RESPONSE_H

#include <framework.h>

namespace engine {

    class http_response {
    public:
        FW_DECLARE_SMARTPOINTERS(http_response)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(http_response)

        http_response();
        ~http_response();

    private:

    };

}

#endif /* ENGINE_HTTP_RESPONSE_H */
