//
// Created by Feo on 01/10/2018.
//

#ifndef MESSAGEN_FIELD_H
#define MESSAGEN_FIELD_H

#include <vector>
#include <string>

#include "message/field_attribute.h"

class class_field {
public:
    class_field();
    ~class_field();

    void name(const std::string& name) noexcept { _name = name; }
    void type(const std::string& type) noexcept { _type = type; }
    void is_array(bool is_array) noexcept { _is_array = is_array; }
    void length(int length) noexcept { _length = length; }

    void add_attribute(field_attribute *attribute) noexcept;

private:
    std::string                     _name;
    std::string                     _type;
    bool                            _is_array;
    int                             _length;
    std::vector<field_attribute*>   _attributes;

};

#endif /* MESSAGEN_FIELD_H */
