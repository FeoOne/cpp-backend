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
    std::string filesystem::read_whole_file(const std::string_view& path) noexcept
    {
        std::ifstream file { path.data() };
        return  { (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() };
    }

}
