//
// Created by Feo on 15/10/2018.
//

#include "codegen/cpp/message_builder_field_builder.h"

#define TPL_NAME        "%NAME%"
#define TPL_TYPE        "%TYPE%"
#define TPL_COUNT       "%COUNT%"

static const char *string_field_template {
    "\tprivate:\n"
    "\t\tconst char *_" TPL_NAME ";\n"
    "\tpublic:\n"
    "\t\tinline void set_" TPL_NAME "(const char *value) noexcept { _" TPL_NAME " = value; }\n"
    "\t\tinline size_t " TPL_NAME "_length() const noexcept { return std::strlen(_" TPL_NAME ") + 1; }\n\n"
};

static const char *integral_field_template {
    "\tprivate:\n"
    "\t\t" TPL_TYPE " _" TPL_NAME ";\n"
    "\tpublic:\n"
    "\t\tinline void set_" TPL_NAME "(" TPL_TYPE " value) noexcept { _" TPL_NAME " = value; }\n"
    "\t\tconstexpr inline size_t " TPL_NAME "_length() const noexcept { return sizeof(" TPL_TYPE "); }\n\n"
};

static const char *integral_array_field_template {
    "\tprivate:\n"
    "\t\tconst " TPL_TYPE " *_" TPL_NAME ";\n"
    "\t\tstatic constexpr size_t _" TPL_NAME "_count { " TPL_COUNT " };\n"
    "\tpublic:\n"
    "\t\tinline void set_" TPL_NAME "(const " TPL_TYPE " *value) noexcept { _" TPL_NAME " = value; }\n"
    "\t\tconstexpr inline size_t " TPL_NAME "_length() const noexcept { return sizeof(" TPL_TYPE ") * _" TPL_NAME "_count; }\n\n"
};

static const char *integral_vector_field_template {
    "\tprivate:\n"
    "\t\tconst " TPL_TYPE " *_" TPL_NAME ";\n"
    "\t\tsize_t _" TPL_NAME "_count;\n"
    "\tpublic:\n"
    "\t\tinline void set_" TPL_NAME "(const " TPL_TYPE " *value, size_t count) noexcept { _"
    TPL_NAME " = value; _" TPL_NAME "_count = count; }\n"
    "\t\tinline size_t " TPL_NAME "_length() const noexcept { return sizeof(" TPL_TYPE ") * _" TPL_NAME "_count; }\n\n"
};

message_builder_field_builder::message_builder_field_builder(const field_presenter *field) noexcept :
        _field { field }
{
}

std::string message_builder_field_builder::build() const noexcept
{
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
            { "u8", integral_array_field_template },
            { "s8", integral_array_field_template },
            { "u16", integral_array_field_template },
            { "s16", integral_array_field_template },
            { "u32", integral_array_field_template },
            { "s32", integral_array_field_template },
            { "u64", integral_array_field_template },
            { "s64", integral_array_field_template },
    };

    static const std::unordered_map<std::string, const char *> vector_templates {
            { "u8", integral_vector_field_template },
            { "s8", integral_vector_field_template },
            { "u16", integral_vector_field_template },
            { "s16", integral_vector_field_template },
            { "u32", integral_vector_field_template },
            { "s32", integral_vector_field_template },
            { "u64", integral_vector_field_template },
            { "s64", integral_vector_field_template },
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
    stl::string::replace_all(content, TPL_TYPE, _field->type());

    return content;
}
