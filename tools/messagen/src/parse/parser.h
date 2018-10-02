/**
 * @file parser.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef MESSAGEN_PARSER_H
#define MESSAGEN_PARSER_H

#include <vector>
#include <functional>
#include <unordered_map>

#include "main/lexertk.h"
#include "message/message_class.h"

enum class parse_state {
    undefined,
    new_message,
    start_scope,
    message_scope,
    field,
    field_type,
    field_type_ex,
    field_array,
};

class parser {
public:
    parser();
    ~parser();

    void parse(lexertk::generator& generator) noexcept;

private:
    parse_state                                                             _state;
    message_class *                                                         _current_message;
    class_field *                                                           _current_field;
    field_attribute *                                                       _current_attribute;
    std::vector<message_class *>                                            _messages;
    std::unordered_map<parse_state, std::function<void(lexertk::token&)>>   _processor;

    void set_state(parse_state state) noexcept;

    void process_undefined_state(lexertk::token& token) noexcept;
    void process_new_message_state(lexertk::token& token) noexcept;
    void process_start_scope_state(lexertk::token& token) noexcept;
    void process_message_scope_state(lexertk::token& token) noexcept;
    void process_field_state(lexertk::token& token) noexcept;
    void process_field_type_state(lexertk::token& token) noexcept;
    void process_field_type_ex_state(lexertk::token& token) noexcept;
    void process_field_array_state(lexertk::token& token) noexcept;

};

#endif /* MESSAGEN_PARSER_H */
