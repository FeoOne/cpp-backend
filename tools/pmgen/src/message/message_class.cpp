/**
 * @file message_class.cpp
 * @author Feo
 * @date 01/10/2018
 * @brief
 */

#include "message/message_class.h"

message_class::message_class() :
        _name { "" }
{
}

message_class::~message_class()
{
}

void message_class::commit_field(const class_field *field) noexcept
{
    _fields.push_back(field);
}
