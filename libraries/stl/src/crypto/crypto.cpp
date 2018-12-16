/**
 * @file crypto.cpp
 * @author Feo
 * @date 16/12/2018
 * @brief
 */

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include "logger/log_manager.h"

#include "crypto/crypto.h"

namespace stl {

    // static
    std::string crypto::base64_encode(const char *text) noexcept
    {
        BIO *bio, *b64;
        BUF_MEM *bufferPtr;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        bio = BIO_push(b64, bio);

        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Ignore newlines - write everything in one line
        BIO_write(bio, text, static_cast<int>(std::strlen(text)));
        BIO_flush(bio);
        BIO_get_mem_ptr(bio, &bufferPtr);
        BIO_set_close(bio, BIO_NOCLOSE);

        std::string result { bufferPtr->data, bufferPtr->length };

        BIO_free_all(bio);

        return result;
    }

    size_t calculate_decoded_string_length(const char* b64input) noexcept
    {
        size_t len { std::strlen(b64input) };
        size_t padding { 0 };

        if (b64input[len-1] == '=' && b64input[len-2] == '=') {// last two chars are =
            padding = 2;
        } else if (b64input[len - 1] == '=') {// last char is =
            padding = 1;
        }

        return (len * 3) / 4 - padding;
    }

    // static
    std::string crypto::base64_decode(const char *b64input) noexcept
    {
        BIO *bio, *b64;

        auto string_length { calculate_decoded_string_length(b64input) };
        std::string result;
        result.reserve(string_length + 1);
        result[string_length] = 0;

        bio = BIO_new_mem_buf(b64input, -1);
        b64 = BIO_new(BIO_f_base64());
        bio = BIO_push(b64, bio);

        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Do not use newlines to flush buffer
        auto length { BIO_read(bio, result.data(), static_cast<int>(std::strlen(b64input))) };
        logassert(static_cast<int>(string_length) == length,
                "Length should equal string_length, else something went horribly wrong.");
        BIO_free_all(bio);

        return result;
    }

}
