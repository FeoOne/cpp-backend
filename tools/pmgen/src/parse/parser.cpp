/**
 * @file parser.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "parse/parser.h"

parser::parser() :
        _state { parse_state::global_scope },
        _context {},
        _current_message { nullptr },
        _current_field { nullptr },
        _current_attribute { nullptr },
        _processor {
            { parse_state::global_scope, std::bind(&parser::process_global_scope_state, this, std::placeholders::_1) },
            { parse_state::message_declaration, std::bind(&parser::process_message_declaration_state, this, std::placeholders::_1) },
            { parse_state::message_scope, std::bind(&parser::process_message_scope_state, this, std::placeholders::_1) },
            { parse_state::field_scope, std::bind(&parser::process_field_scope_state, this, std::placeholders::_1) },
            { parse_state::namespace_declaration, std::bind(&parser::process_namespace_declaration_state, this, std::placeholders::_1) },
        },
        _global_scope_processor {
            { "message", std::bind(&parser::process_global_scope_message, this, std::placeholders::_1) },
            { "namespace", std::bind(&parser::process_global_scope_namespace, this, std::placeholders::_1) },
        }
{

}

parser::~parser()
{

}

void parser::parse(lexertk::generator& generator) noexcept
{
    size_t index { 0 };
    while (index < generator.size()) {
        auto token { generator[index] };
        ++index;

        _processor[_state](token);
    }

//    assert(false);
}

void parser::set_state(parse_state state) noexcept
{
    _state = state;
}

// global_scope
void parser::process_global_scope_state(lexertk::token& token) noexcept
{
    assert(token.type == lexertk::token::token_type::e_symbol);

    auto it = _global_scope_processor.find(token.value);
    assert(it != _global_scope_processor.end());

    it->second(token);
}

// message_declaration
void parser::process_message_declaration_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);

    // name
    if (token.type == lexertk::token::token_type::e_symbol) {
        assert(token.value.length() > 2);
        assert(token.value.length() < 32);

        _current_message->name(token.value);

        return;
    }

    // {
    if (token.type == lexertk::token::token_type::e_lcrlbracket) {
        set_state(parse_state::message_scope);

        return;
    }

    assert(false);
}

// message_scope
void parser::process_message_scope_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);

    // field
    if (token.type == lexertk::token::token_type::e_symbol) {
        assert(token.value.length() > 2);
        assert(token.value.length() < 32);

        _current_field = new class_field;
        _current_field->name(token.value);

        set_state(parse_state::field_scope);

        return;
    }

    // }
    if (token.type == lexertk::token::token_type::e_rcrlbracket) {
        _context.commit_message(_current_message);
        _current_message = nullptr;

        set_state(parse_state::global_scope);

        return;
    }

    assert(false);
}

// field_scope
void parser::process_field_scope_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);
    assert(_current_field != nullptr);

    // :
    if (token.type == lexertk::token::token_type::e_colon) {
        return;
    }

    // type
    if (token.type == lexertk::token::token_type::e_symbol) {
        _current_field->type(token.value);

        return;
    }

    // [
    if (token.type == lexertk::token::token_type::e_lsqrbracket) {
        _current_field->is_array(true);

        return;
    }

    // array length
    if (token.type == lexertk::token::token_type::e_number) {
        assert(_current_field->is_array());

        _current_field->length(std::stoi(token.value));

        return;
    }

    // ]
    if (token.type == lexertk::token::token_type::e_lsqrbracket) {
        assert(_current_field->is_array());

        return;
    }

    // ;
    if (token.type == lexertk::token::token_type::e_eof) {
        _current_message->commit_field(_current_field);
        _current_field = nullptr;

        set_state(parse_state::message_scope);

        return;
    }
}

void parser::process_namespace_declaration_state(lexertk::token& token) noexcept
{
    // namespace name
    if (token.type == lexertk::token::token_type::e_symbol) {
        assert(token.value.length() > 2);
        assert(token.value.length() < 32);

        _context.ns(token.value);

        return;
    }

    // ;
    if (token.type == lexertk::token::token_type::e_eof) {
        assert(_context.ns().length() > 0);

        set_state(parse_state::global_scope);

        return;
    }
}

// global_scope message
void parser::process_global_scope_message(lexertk::token& token) noexcept
{
    _current_message = new message_class;

    set_state(parse_state::message_declaration);
}

// global_scope namespace
void parser::process_global_scope_namespace(lexertk::token& token) noexcept
{
    set_state(parse_state::namespace_declaration);
}
