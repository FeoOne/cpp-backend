/**
 * @file message_presenter.cpp
 * @author Feo
 * @date 01/10/2018
 * @brief
 */

#include "data/message_presenter.h"

message_presenter::message_presenter() :
        _name { "" }
{
}

void message_presenter::add_field(const field_presenter *field) noexcept
{
    _fields.push_back(field);
}
