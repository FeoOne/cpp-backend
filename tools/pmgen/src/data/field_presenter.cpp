//
// Created by Feo on 01/10/2018.
//

#include "data/field_presenter.h"

field_presenter::field_presenter() :
        _name { "" },
        _type { "" },
        _is_array { false },
        _length { -1 },
        _attributes {}
{
}

void field_presenter::add_attribute(attribute_presenter *attribute) noexcept
{
    _attributes.push_back(attribute);
}
