/**
 * @file string.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef STL_STRING_H
#define STL_STRING_H

#include <random>
#include <string>
#include <string_view>

#include "scalar/numeric.h"

namespace stl {

    class string {
    public:
        static std::string to_uppercase(const std::string& str) noexcept;
        static void make_uppercase(std::string& str) noexcept;

        static void fill_with_random_symbols(char *string, size_t length) noexcept;

        static void replace(std::string& str, const std::string& pattern, const std::string& text) noexcept;
        static void replace_all(std::string& str, const std::string& pattern, const std::string& text) noexcept;

    };

}

#endif /* STL_STRING_H */
