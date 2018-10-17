/**
 * @file message_field_builder.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "codegen/cpp/message_field_builder.h"

#define TPL_NAME        "%NAME%"
#define TPL_TYPE        "%TYPE%"
#define TPL_OFFSET      "%OFFSET%"
#define TPL_COUNT       "%COUNT%"

#define INDEX_SIZE      "sizeof(u16)"

static const char *string_field_template {
    "\t\tinline " TPL_TYPE "get_" TPL_NAME "() const noexcept { return reinterpret_cast<" TPL_TYPE
        ">(&memory()[" TPL_NAME "_offset()]); }\n"
    "\t\tinline size_t " TPL_NAME "_offset() const noexcept { return " TPL_OFFSET "; }\n"
    "\t\tinline size_t " TPL_NAME "_length() const noexcept { return std::strlen(get_" TPL_NAME "()) + 1; }\n\n"
};

static const char *integral_field_template {
    "\t\tinline " TPL_TYPE " get_" TPL_NAME "() const noexcept { return *reinterpret_cast<const " TPL_TYPE
        " *>(&memory()[" TPL_NAME "_offset()]); }\n"
    "\t\tinline size_t " TPL_NAME "_offset() const noexcept { return " TPL_OFFSET "; }\n"
    "\t\tconstexpr inline size_t " TPL_NAME "_length() const noexcept { return sizeof(" TPL_TYPE "); }\n\n"
};

static const char *integral_array_template {
    "\t\tinline const " TPL_TYPE " *get_" TPL_NAME "() const noexcept { return reinterpret_cast<const " TPL_TYPE
    " *>(&memory()[" TPL_NAME "_offset()]); }\n"
    "\t\tconstexpr inline size_t " TPL_NAME "_count() const noexcept { return " TPL_COUNT "; }\n"
    "\t\tinline size_t " TPL_NAME "_offset() const noexcept { return " TPL_OFFSET "; }\n"
    "\t\tconstexpr inline size_t " TPL_NAME "_length() const noexcept { return sizeof(" TPL_TYPE ") * " TPL_NAME "_count(); }\n\n"
};

static const char *integral_vector_template {
    "\t\tinline const " TPL_TYPE " *get_" TPL_NAME "() const noexcept { return reinterpret_cast<const " TPL_TYPE
    " *>(&memory()[" TPL_NAME "_offset() + " INDEX_SIZE "]); }\n"
    "\t\tinline size_t " TPL_NAME "_count() const noexcept { return *reinterpret_cast<const u16 *>(&memory()["
    TPL_NAME "_offset()]); }\n"
    "\t\tinline size_t " TPL_NAME "_offset() const noexcept { return " TPL_OFFSET "; }\n"
    "\t\tinline size_t " TPL_NAME "_length() const noexcept { return sizeof(" TPL_TYPE ") * " TPL_NAME
    "_count() + " INDEX_SIZE "; }\n\n"
};

message_field_builder::message_field_builder(const field_presenter *field,
                                             const field_presenter *previous_field) noexcept :
        _field { field },
        _previous_field { previous_field }
{
}

std::string message_field_builder::build() const noexcept
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

    static const std::unordered_map<std::string, const char *> array_templates {
            { "u8", integral_array_template },
            { "s8", integral_array_template },
            { "u16", integral_array_template },
            { "s16", integral_array_template },
            { "u32", integral_array_template },
            { "s32", integral_array_template },
            { "u64", integral_array_template },
            { "s64", integral_array_template },
    };

    static const std::unordered_map<std::string, const char *> vector_templates {
            { "u8", integral_vector_template },
            { "s8", integral_vector_template },
            { "u16", integral_vector_template },
            { "s16", integral_vector_template },
            { "u32", integral_vector_template },
            { "s32", integral_vector_template },
            { "u64", integral_vector_template },
            { "s64", integral_vector_template },
    };

    std::string content;

    if (_field->is_array()) {
        if (_field->length() != -1) {
            auto it { array_templates.find(_field->type()) };
            if (it == array_templates.end()) {
                logcrit("Unknown type: %s.", _field->type().data());
            }

            content.assign(it->second);

            stl::string::replace_all(content, TPL_COUNT, std::to_string(_field->length()));
        } else {
            auto it { vector_templates.find(_field->type()) };
            if (it == vector_templates.end()) {
                logcrit("Unknown type: %s.", _field->type().data());
            }

            content.assign(it->second);
        }
    } else {
        auto it { templates.find(_field->type()) };
        if (it == templates.end()) {
            logcrit("Unknown type: %s.", _field->type().data());
        }

        content.assign(it->second);
    }

    stl::string::replace_all(content, TPL_NAME, _field->name());
    stl::string::replace_all(content, TPL_TYPE, types.at(_field->type()));

    std::string offset { "0" };
    if (_previous_field != nullptr) {
        offset = _previous_field->name() + "_offset() + " + _previous_field->name() + "_length()";
    }
    stl::string::replace(content, TPL_OFFSET, offset);

    return content;
}
