/**
 * @file parser.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "parse/parser.h"

parser::parser() :
        _state { parse_state::undefined },
        _current_message { nullptr },
        _current_field { nullptr },
        _current_attribute { nullptr },
        _messages {},
        _processor {
            { parse_state::undefined, std::bind(&parser::process_undefined_state, this, std::placeholders::_1) },
            { parse_state::new_message, std::bind(&parser::process_new_message_state, this, std::placeholders::_1) },
            { parse_state::start_scope, std::bind(&parser::process_start_scope_state, this, std::placeholders::_1) },
            { parse_state::message_scope, std::bind(&parser::process_message_scope_state, this, std::placeholders::_1) },
            { parse_state::field, std::bind(&parser::process_field_state, this, std::placeholders::_1) },
            { parse_state::field_type, std::bind(&parser::process_field_type_state, this, std::placeholders::_1) },
            { parse_state::field_type_ex, std::bind(&parser::process_field_type_ex_state, this, std::placeholders::_1) },
            { parse_state::field_array, std::bind(&parser::process_field_array_state, this, std::placeholders::_1) },
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

    assert(false);
}

void parser::set_state(parse_state state) noexcept
{
    _state = state;
}

// undefined
void parser::process_undefined_state(lexertk::token& token) noexcept
{
    assert(token.type == lexertk::token::token_type::e_symbol);
    assert(token.value == "message");

    _current_message = new message_class;

    set_state(parse_state::new_message);
}

// new_message
void parser::process_new_message_state(lexertk::token& token) noexcept
{
    assert(token.type == lexertk::token::token_type::e_symbol);
    assert(token.value.length() > 2);
    assert(token.value.length() < 32);
    assert(_current_message != nullptr);

    _current_message->name(token.value);

    set_state(parse_state::start_scope);
}

// start_scope
void parser::process_start_scope_state(lexertk::token& token) noexcept
{
    assert(token.type == lexertk::token::token_type::e_lcrlbracket);
    assert(_current_message != nullptr);

    set_state(parse_state::message_scope);
}

// message_scope
void parser::process_message_scope_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);

    if (token.type == lexertk::token::token_type::e_symbol) {
        assert(token.value.length() > 2);
        assert(token.value.length() < 32);

        _current_field = new class_field;
        _current_field->name(token.value);

        set_state(parse_state::field);

        return;
    }

    if (token.type == lexertk::token::token_type::e_rcrlbracket) {
        _messages.push_back(_current_message);
        _current_message = nullptr;

        set_state(parse_state::undefined);

        return;
    }

    assert(false);
}

// field
void parser::process_field_state(lexertk::token& token) noexcept
{
    assert(token.type == lexertk::token::token_type::e_colon);
    assert(_current_message != nullptr);
    assert(_current_field != nullptr);

    set_state(parse_state::field_type);
}

// field_type
void parser::process_field_type_state(lexertk::token& token) noexcept
{
    assert(token.type == lexertk::token::token_type::e_symbol);
    assert(_current_message != nullptr);
    assert(_current_field != nullptr);

    _current_field->type(token.value);

    set_state(parse_state::field_type_ex);
}

// field_type_ex
void parser::process_field_type_ex_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);
    assert(_current_field != nullptr);

    if (token.type == lexertk::token::token_type::e_lsqrbracket) {
        _current_field->is_array(true);

        set_state(parse_state::field_array);

        return;
    }

    if (token.type == lexertk::token::token_type::e_eof) {
        _current_message->add_field(_current_field);
        _current_field = nullptr;

        set_state(parse_state::message_scope);

        return;
    }

    assert(false);
}

// field_array
void parser::process_field_array_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);
    assert(_current_field != nullptr);

    if (token.type == lexertk::token::token_type::e_number) {
        _current_field->length(std::stoi(token.value));

        return;
    }

    if (token.type == lexertk::token::token_type::e_rsqrbracket) {
        set_state(parse_state::field_type_ex);

        return;
    }

    assert(false);
}
