/**
 * @file string.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include "scalar/string.h"

namespace stl {

    // static
    void string::make_uppercase(std::string& str) noexcept
    {
        std::transform(str.begin(), str.end(), str.begin(), toupper);
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
