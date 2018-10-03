/**
 * @file field_builder.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "write/field_builder.h"

#define TPL_TYPE        "%TYPE%"
#define TPL_NAME        "%NAME%"
#define TPL_OFFSET      "%OFFSET%"
#define TPL_SIZE        "%SIZE%"

static const char *field_template {
    "\t\t" TPL_TYPE "get_" TPL_NAME "() const noexcept { return memory()[%NAME%_offset()]; }\n"
    "\t\tsize_t " TPL_NAME "_offset() const noexcept { return " TPL_OFFSET "; }\n"
    "\t\tsize_t " TPL_NAME "_length() const noexcept { return " TPL_SIZE "; }\n\n"
};

field_builder::field_builder(field_builder *prev) noexcept :
        _prev { prev },
        _content { field_template },
        _name { "" }
{
}

void field_builder::set_name(const std::string& name) noexcept
{
    _name = name;
    stl::string::replace_all(_content, TPL_NAME, name);
}

void field_builder::set_type(const std::string& type) noexcept
{
    static const std::unordered_map<std::string, std::string> types {
        { "string", "const char *" },
        { "u8", "u8 " },
        { "s8", "s8 " },
        { "u16", "u16 " },
        { "s16", "s16 " },
        { "u32", "u32 " },
        { "s32", "s32 " },
        { "u64", "u64 " },
        { "s64", "s64 " },
    };

    stl::string::replace(_content, TPL_TYPE, types.at(type));

    std::string size;
    if (type == "string") {
        size = "std::strlen(get_" + _name + "()) + 1";
    } else {
        size = "sizeof(" + type + ")";
    }
    stl::string::replace(_content, TPL_SIZE, size);
}

std::string field_builder::build() noexcept
{
    std::string offset { "0" };
    if (_prev != nullptr) {
        offset = _prev->name() + "_offset() + " + _prev->name() + "_length()";
    }
    stl::string::replace(_content, TPL_OFFSET, offset);

    return _content;
}
