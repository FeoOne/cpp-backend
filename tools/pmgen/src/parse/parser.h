/**
 * @file parser.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_PARSER_H
#define PMGEN_PARSER_H

#include <vector>
#include <functional>
#include <unordered_map>

#include "main/lexertk.h"
#include "parse/parse_contex.h"

enum class parse_state {
    global_scope,
    message_declaration,
    message_scope,
    field_scope,
    namespace_declaration,
};

class parser {
public:
    parser();
    ~parser();

    void parse(lexertk::generator& generator) noexcept;

    parse_contex& contex() noexcept { return _contex; }

private:
    parse_state                                                             _state;
    parse_contex                                                            _context;

    message_class *                                                         _current_message;
    class_field *                                                           _current_field;
    field_attribute *                                                       _current_attribute;

    std::unordered_map<parse_state, std::function<void(lexertk::token&)>>   _processor;
    std::unordered_map<std::string, std::function<void(lexertk::token&)>>   _global_scope_processor;

    void set_state(parse_state state) noexcept;

    void process_global_scope_state(lexertk::token& token) noexcept;
    void process_message_declaration_state(lexertk::token& token) noexcept;
    void process_message_scope_state(lexertk::token& token) noexcept;
    void process_field_scope_state(lexertk::token& token) noexcept;
    void process_namespace_declaration_state(lexertk::token& token) noexcept;

    void process_global_scope_message(lexertk::token& token) noexcept;
    void process_global_scope_namespace(lexertk::token& token) noexcept;

};

#endif /* PMGEN_PARSER_H */
