/**
 * @file filesystem.h
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#ifndef STL_FILESYSTEM_H
#define STL_FILESYSTEM_H

#include <string>
#include <string_view>

#include "memory/memory.h"

namespace stl {

    class filesystem {
    public:
        STL_DELETE_ALL_DEFAULT(filesystem)

        static std::string read_text_file(const std::string_view& path) noexcept;
        static void write_text_file(const std::string_view& path, const std::string& text) noexcept;

    private:

    };

}

#endif /* STL_FILESYSTEM_H */
