/**
 * @file class_presenter.cpp
 * @author Feo
 * @date 01/10/2018
 * @brief
 */

#include "data/class_presenter.h"

class_presenter::class_presenter() :
        _name { "" }
{
}

void class_presenter::add_field(const field_presenter *field) noexcept
{
    _fields.push_back(field);
}
