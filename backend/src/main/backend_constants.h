/**
 * @file constants.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef BACKEND_CONSTANTS_H
#define BACKEND_CONSTANTS_H

#include <framework.h>

namespace backend {

    class backend_constants {
    public:
        static constexpr std::string_view WEB_SERVER_HEADER { "bitpt-httpd " };
        static constexpr size_t WEB_SERVER_PORT { 8888 };

    };

}

#endif /* BACKEND_CONSTANTS_H */
