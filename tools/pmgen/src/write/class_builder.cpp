/**
 * @file class_builder.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include <stl.h>

#include "write/class_builder.h"

#define TPL_CLASSNAME       "%CLASSNAME%"
#define TPL_PUBLICSCOPE     "%PUBLICSCOPE%"
#define TPL_PRIVATESCOPE    "%PRIVATESCOPE%"

static const char *class_template {
    "\tclass " TPL_CLASSNAME " : public pmp::message {\n"
    "\tpublic:\n"
    TPL_PUBLICSCOPE
    "\t};\n\n"
};

class_builder::class_builder() :
        _content { class_template }
{
}

void class_builder::set_name(const std::string& name) noexcept
{
    stl::string::replace(_content, TPL_CLASSNAME, name);
}

const std::string& class_builder::build() noexcept
{
    std::string public_scope { "" };
    for (auto field: _fields) {
        public_scope += field->build();
    }
    stl::string::replace(_content, TPL_PUBLICSCOPE, public_scope);

    return _content;
}
