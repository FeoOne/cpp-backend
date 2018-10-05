/**
 * @file field_builder.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "codegen/cpp/field_builder.h"

#define TPL_TYPE        "%TYPE%"
#define TPL_NAME        "%NAME%"
#define TPL_OFFSET      "%OFFSET%"

static const char *string_field_template {
    "\t\t" TPL_TYPE "get_" TPL_NAME "() const noexcept { return reinterpret_cast<" TPL_TYPE ">(&memory()[%NAME%_offset()]); }\n"
    "\t\tsize_t " TPL_NAME "_offset() const noexcept { return " TPL_OFFSET "; }\n"
    "\t\tsize_t " TPL_NAME "_length() const noexcept { return std::strlen(get_" TPL_NAME "()) + 1; }\n\n"
};

static const char *integral_field_template {
    "\t\t" TPL_TYPE " get_" TPL_NAME "() const noexcept { return *reinterpret_cast<const " TPL_TYPE " *>(&memory()[%NAME%_offset()]); }\n"
    "\t\tsize_t " TPL_NAME "_offset() const noexcept { return " TPL_OFFSET "; }\n"
    "\t\tsize_t " TPL_NAME "_length() const noexcept { return sizeof(" TPL_TYPE "); }\n\n"
};

field_builder::field_builder(const field_builder::sptr& prev) noexcept :
        _prev { prev },
        _content {},
        _name { "" }
{
}

void field_builder::set_name(const std::string& name) noexcept
{
    _name = name;
}

void field_builder::set_type(const std::string& type) noexcept
{
    static const std::unordered_map<std::string, std::string> types {
        { "string", "const char *" },
        { "u8", "u8" },
        { "s8", "s8" },
        { "u16", "u16" },
        { "s16", "s16" },
        { "u32", "u32" },
        { "s32", "s32" },
        { "u64", "u64" },
        { "s64", "s64" },
    };

    static const std::unordered_map<std::string, const char *> templates {
        { "string", string_field_template },
        { "u8", integral_field_template },
        { "s8", integral_field_template },
        { "u16", integral_field_template },
        { "s16", integral_field_template },
        { "u32", integral_field_template },
        { "s32", integral_field_template },
        { "u64", integral_field_template },
        { "s64", integral_field_template },
    };

    _content.assign(templates.at(type));

    stl::string::replace_all(_content, TPL_NAME, _name);
    stl::string::replace_all(_content, TPL_TYPE, types.at(type));
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
