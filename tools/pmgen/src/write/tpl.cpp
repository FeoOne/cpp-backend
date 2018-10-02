/**
 * @file tpl.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "write/tpl.h"

tpl::tpl(const std::string& filepath) noexcept
{
    try {
        std::ifstream file { filepath };
        _content = { (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() };
    }
    catch (std::exception&) {
        _content = "";
    }
}

tpl::~tpl()
{
}

void tpl::replace(const std::string_view& pattern, const std::string& text) noexcept
{

}
