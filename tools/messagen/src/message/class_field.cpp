//
// Created by Feo on 01/10/2018.
//

#include "message/class_field.h"

class_field::class_field() :
        _name { "" },
        _type { "" },
        _is_array { false },
        _length { -1 },
        _attributes {}
{

}

class_field::~class_field()
{

}

void class_field::add_attribute(field_attribute *attribute) noexcept
{
    _attributes.push_back(attribute);
}
