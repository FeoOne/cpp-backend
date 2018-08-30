//
// Created by Feo on 16/08/2018.
//

#include "logger/log_manager.h"

#include "config/command_line_option_processor.h"

namespace groot {

    static const std::unordered_map<command_line_option_type, GOptionArg> ARG_TYPE {
            { command_line_option_type::NONE,            G_OPTION_ARG_NONE           },
            { command_line_option_type::INT,             G_OPTION_ARG_INT            },
            { command_line_option_type::DOUBLE,          G_OPTION_ARG_DOUBLE         },
            { command_line_option_type::STRING,          G_OPTION_ARG_STRING         },
            { command_line_option_type::FILENAME,        G_OPTION_ARG_FILENAME       },
            { command_line_option_type::STRING_ARRAY,    G_OPTION_ARG_STRING_ARRAY   },
            { command_line_option_type::FILENAME_ARRAY,  G_OPTION_ARG_FILENAME_ARRAY },
    };

    static void setup_entry(GOptionEntry *entry,
                            command_line_option_type type,
                            void *ptr,
                            const std::string_view& long_name,
                            char short_name,
                            const std::string_view& description,
                            const std::string_view& arg_description,
                            bool is_optional,
                            bool is_hidden) noexcept
    {
        entry->long_name = long_name.data();
        entry->short_name = short_name;
        entry->description = description.data();
        entry->arg_description = arg_description.data();

        entry->flags = G_OPTION_FLAG_NONE;
        if (is_optional) {
            entry->flags |= G_OPTION_FLAG_OPTIONAL_ARG;
        }
        if (is_hidden) {
            entry->flags |= G_OPTION_FLAG_HIDDEN;
        }
        if (type == command_line_option_type::NONE) {
            entry->flags |= G_OPTION_FLAG_NO_ARG;
        }

        entry->arg = ARG_TYPE.at(type);
        entry->arg_data = ptr;
    }

    command_line_option_processor::command_line_option_processor(int argc,
                                                                 char **argv,
                                                                 const std::string_view& app_description) noexcept :
            _argc { argc },
            _argv { argv },
            _groups {},
            _context { g_option_context_new(app_description.data()) },
            _options {}
    {
    }

    command_line_option_processor::~command_line_option_processor()
    {
        g_option_context_free(_context);
    }

    void command_line_option_processor::push_group(const std::string_view& name,
                                                   const std::string_view& description,
                                                   const std::string_view& detailed_description) noexcept
    {
        auto group = g_option_group_new(name.data(),
                                        description.data(),
                                        detailed_description.data(),
                                        nullptr,
                                        nullptr);
        _groups.push(group);
    }

    void command_line_option_processor::add_option(command_line_option_type type,
                                                   void *ptr,
                                                   const std::string_view& long_name,
                                                   char short_name,
                                                   const std::string_view& description,
                                                   const std::string_view& arg_description,
                                                   bool is_optional,
                                                   bool is_hidden) noexcept
    {
        setup_entry(&_options[_groups.back()].emplace_back(),
                    type,
                    ptr,
                    long_name,
                    short_name,
                    description,
                    arg_description,
                    is_optional,
                    is_hidden);
    }

    void command_line_option_processor::process() noexcept
    {
        GError *error { nullptr };

        while (!_groups.empty()) {
            auto group = _groups.front();
            _groups.pop();

            auto& options = _options[group];
            options.push_back({ nullptr, 0, 0, G_OPTION_ARG_NONE, nullptr, nullptr, nullptr });

            g_option_group_add_entries(group, options.data());
            g_option_context_add_group(_context, group);

            if (_groups.empty()) {
                g_option_context_set_main_group(_context, group);
            }
        }

        if (!g_option_context_parse(_context, &_argc, &_argv, &error)) {
            logemerg("Command line arguments parsing failed: %s", error->message);
        }
    }

}
