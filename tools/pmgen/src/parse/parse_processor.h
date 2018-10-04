/**
 * @file parse_processor.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_PARSER_H
#define PMGEN_PARSER_H

#include <vector>
#include <functional>
#include <unordered_map>

#include "parse/lexer.h"
#include "parse/parse_contex.h"

enum class parsing_state {
    global_scope,
    message_declaration,
    message_scope,
    field_scope,
    namespace_declaration,
    opcode_offset,
};

class parse_processor {
public:
    STL_DECLARE_SMARTPOINTERS(parse_processor)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(parse_processor)

    parse_processor();
    ~parse_processor() = default;

    void parse(lexer *lex) noexcept;

    parse_contex& contex() noexcept { return _context; }

private:
    parsing_state                                                           _state;
    parse_contex                                                            _context;

    class_presenter *                                                       _current_message;
    field_presenter *                                                       _current_field;
    attribute_presenter *                                                   _current_attribute;

    std::unordered_map<parsing_state, std::function<bool(lexertk::token&)>> _processor;
    std::unordered_map<std::string, std::function<bool(lexertk::token&)>>   _global_scope_processor;

    void set_state(parsing_state state) noexcept;

    bool process_global_scope_state(lexertk::token& token) noexcept;
    bool process_message_declaration_state(lexertk::token& token) noexcept;
    bool process_message_scope_state(lexertk::token& token) noexcept;
    bool process_field_scope_state(lexertk::token& token) noexcept;
    bool process_namespace_declaration_state(lexertk::token& token) noexcept;
    bool process_opcode_offset_state(lexertk::token& token) noexcept;

    bool process_global_scope_message(lexertk::token& token) noexcept;
    bool process_global_scope_namespace(lexertk::token& token) noexcept;
    bool process_global_scope_opcode_offset(lexertk::token& token) noexcept;

};

#endif /* PMGEN_PARSER_H */
