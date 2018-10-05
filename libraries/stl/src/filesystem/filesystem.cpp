/**
 * @file filesystem.cpp
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#include <fstream>

#include "filesystem/filesystem.h"

namespace stl {

    // static
    std::string filesystem::read_text_file(const std::string_view& path) noexcept
    {
        std::ifstream file { path.data() };
        std::string text { (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() };
        file.close();
        return text;
    }

    // static
    void filesystem::write_text_file(const std::string_view& path, const std::string& text) noexcept
    {
        std::ofstream file { path.data() };
        file << text;
        file.close();
    }

}
