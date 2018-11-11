/**
 * @file string.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "scalar/string.h"

namespace stl {

    // static
    std::string string::to_uppercase(const std::string& str) noexcept
    {
        auto result { str };
        make_uppercase(result);
        return result;
    }

    // static
    void string::make_uppercase(std::string& str) noexcept
    {
        std::transform(str.begin(), str.end(), str.begin(), toupper);
    }

    // static
    void string::fill_with_random_symbols(char *string, size_t length) noexcept
    {
        static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<size_t >dist(0, sizeof(alphanum));

        for (size_t i = 0; i < length; ++i) {
            string[i] = alphanum[dist(mt)];
        }

        string[length] = 0;
    }

    // static
    void string::replace(std::string &str, const std::string& pattern, const std::string& text) noexcept
    {
        size_t index { str.find(pattern) };
        if (index == std::string::npos) {
            return;
        }

        str.replace(index, pattern.length(), text);
    }

    // static
    void string::replace_all(std::string &str, const std::string& pattern, const std::string& text) noexcept
    {
        size_t index { 0 };
        while (true) {
            index = str.find(pattern, index);
            if (index == std::string::npos) {
                break;
            }

            str.replace(index, pattern.length(), text);
            index += text.length();
        }
    }

}
