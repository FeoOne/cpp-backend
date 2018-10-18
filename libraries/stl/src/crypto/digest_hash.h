/**
 * @file digest_hash.h
 * @author Feo
 * @date 18/10/2018
 * @brief
 */

#ifndef STL_DIGEST_HASH_H
#define STL_DIGEST_HASH_H

#include <array>

#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

#include "main/tools.h"
#include "logger/log_manager.h"
#include "scalar/numeric.h"
#include "memory/memory.h"

namespace stl {

    using hash_create_fn = const EVP_MD *();

    template<hash_create_fn FN, u32 L>
    class digest_hash {
    public:
        STL_DECLARE_SMARTPOINTERS(digest_hash<FN STL_COMMA() L>)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(digest_hash)

        static constexpr size_t digest_length { L };

        digest_hash() :
                _context {},
                _digest {}
        {
            EVP_MD_CTX_init(&_context);
            EVP_DigestInit_ex(&_context, FN(), nullptr);

            _digest.fill(0);
        }

        ~digest_hash() {
            EVP_MD_CTX_cleanup(&_context);
        }

        inline void update(const char *data) noexcept {
            EVP_DigestUpdate(&_context, data, std::strlen(data));
        }

        inline void finalize() noexcept {
            unsigned int length { 0 };
            EVP_DigestFinal_ex(&_context, _digest.data(), &length);
            logassert(length == digest_length, "Finalize failed.");
        }

        inline const u8 *digest() const noexcept { return _digest.data(); }

    private:
        EVP_MD_CTX                      _context;
        std::array<u8, digest_length>   _digest;

    };

    using md5_hash = digest_hash<EVP_md5, MD5_DIGEST_LENGTH>;
    using sha1_hash = digest_hash<EVP_sha1, SHA_DIGEST_LENGTH>;

}

#endif /* STL_DIGEST_HASH_H */
