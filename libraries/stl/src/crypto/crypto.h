/**
 * @file crypto.h
 * @author Feo
 * @date 16/12/2018
 * @brief
 */

#ifndef STL_CRYPTO_H
#define STL_CRYPTO_H

#include <string>

namespace stl {

    class crypto {
    public:
        static std::string base64_encode(const char *text) noexcept;
        static std::string base64_decode(const char *text) noexcept;

    private:

    };

}

#endif /* STL_CRYPTO_H */
