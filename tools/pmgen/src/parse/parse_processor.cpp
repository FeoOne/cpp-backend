/**
 * @file parse_processor.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "parse/parse_processor.h"

parse_processor::parse_processor() :
        _state { parsing_state::global_scope },
        _context { parsing_context::make_unique() },
        _current_message { nullptr },
        _current_field { nullptr },
        _current_attribute { nullptr },
        _processor {
            { parsing_state::global_scope, std::bind(&parse_processor::process_global_scope_state, this, std::placeholders::_1) },
            { parsing_state::message_declaration, std::bind(&parse_processor::process_message_declaration_state, this, std::placeholders::_1) },
            { parsing_state::message_scope, std::bind(&parse_processor::process_message_scope_state, this, std::placeholders::_1) },
            { parsing_state::field_scope, std::bind(&parse_processor::process_field_scope_state, this, std::placeholders::_1) },
            { parsing_state::namespace_declaration, std::bind(&parse_processor::process_namespace_declaration_state, this, std::placeholders::_1) },
            { parsing_state::opcode_offset, std::bind(&parse_processor::process_opcode_offset_state, this, std::placeholders::_1) },
        },
        _global_scope_processor {
            { "message", std::bind(&parse_processor::process_global_scope_message, this, std::placeholders::_1) },
            { "namespace", std::bind(&parse_processor::process_global_scope_namespace, this, std::placeholders::_1) },
            { "opcode_offset", std::bind(&parse_processor::process_global_scope_opcode_offset, this, std::placeholders::_1) },
        }
{
}

bool parse_processor::parse(lexer *lex) noexcept
{
    size_t index { 0 };
    auto& generator { *lex->generator() };
    while (index < generator.size()) {
        auto token { generator[index] };
        ++index;

        if (!_processor[_state](token)) {
            return false;
        }
    }

    return true;
}

void parse_processor::set_state(parsing_state state) noexcept
{
    _state = state;
}

// global_scope
bool parse_processor::process_global_scope_state(lexertk::token& token) noexcept
{
    if (token.type != lexertk::token::token_type::e_symbol) {
        return false;
    }

    auto it = _global_scope_processor.find(token.value);
    if (it == _global_scope_processor.end()) {
        return false;
    }

    return it->second(token);
}

// message_declaration
bool parse_processor::process_message_declaration_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);

    // name
    if (token.type == lexertk::token::token_type::e_symbol) {
        assert(token.value.length() > 2);
        assert(token.value.length() < 32);

        _current_message->name(token.value);

        return true;
    }

    // {
    if (token.type == lexertk::token::token_type::e_lcrlbracket) {
        set_state(parsing_state::message_scope);

        return true;
    }

    return false;
}

// message_scope
bool parse_processor::process_message_scope_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);

    // field
    if (token.type == lexertk::token::token_type::e_symbol) {
        assert(token.value.length() > 2);
        assert(token.value.length() < 32);

        _current_field = new field_presenter;
        _current_field->name(token.value);

        set_state(parsing_state::field_scope);

        return true;
    }

    // }
    if (token.type == lexertk::token::token_type::e_rcrlbracket) {
        _context->add_message(_current_message);
        _current_message = nullptr;

        set_state(parsing_state::global_scope);

        return true;
    }

    return false;
}

// field_scope
bool parse_processor::process_field_scope_state(lexertk::token& token) noexcept
{
    assert(_current_message != nullptr);
    assert(_current_field != nullptr);

    // :
    if (token.type == lexertk::token::token_type::e_colon) {
        return true;
    }

    // type
    if (token.type == lexertk::token::token_type::e_symbol) {
        _current_field->type(token.value);

        return true;
    }

    // [
    if (token.type == lexertk::token::token_type::e_lsqrbracket) {
        _current_field->is_array(true);

        return true;
    }

    // array length
    if (token.type == lexertk::token::token_type::e_number) {
        assert(_current_field->is_array());

        _current_field->length(std::stoi(token.value));

        return true;
    }

    // ]
    if (token.type == lexertk::token::token_type::e_rsqrbracket) {
        assert(_current_field->is_array());

        return true;
    }

    // ;
    if (token.type == lexertk::token::token_type::e_eof) {
        _current_message->add_field(_current_field);
        _current_field = nullptr;

        set_state(parsing_state::message_scope);

        return true;
    }

    return false;
}

// namespace_declaration
bool parse_processor::process_namespace_declaration_state(lexertk::token& token) noexcept
{
    // namespace name
    if (token.type == lexertk::token::token_type::e_symbol) {
        assert(token.value.length() > 2);
        assert(token.value.length() < 32);

        _context->ns(token.value);

        return true;
    }

    // ;
    if (token.type == lexertk::token::token_type::e_eof) {
        assert(_context->ns().length() > 0);

        set_state(parsing_state::global_scope);

        return true;
    }

    return false;
}

// opcode_offset
bool parse_processor::process_opcode_offset_state(lexertk::token& token) noexcept
{
    // :
    if (token.type == lexertk::token::token_type::e_colon) {
        return true;
    }

    // value
    if (token.type == lexertk::token::token_type::e_number) {
        _context->opcode_offset(static_cast<u32>(std::stoul(token.value)));
        return true;
    }

    // ;
    if (token.type == lexertk::token::token_type::e_eof) {
        assert(_context->opcode_offset() > 0);
        set_state(parsing_state::global_scope);
        return true;
    }

    return false;
}

// global_scope message
bool parse_processor::process_global_scope_message(lexertk::token& token) noexcept
{
    _current_message = new message_presenter;
    set_state(parsing_state::message_declaration);
    return true;
}

// global_scope namespace
bool parse_processor::process_global_scope_namespace(lexertk::token& token) noexcept
{
    set_state(parsing_state::namespace_declaration);
    return true;
}

// global_scope opcode_offset
bool parse_processor::process_global_scope_opcode_offset(lexertk::token& token) noexcept
{
    set_state(parsing_state::opcode_offset);
    return true;
}
