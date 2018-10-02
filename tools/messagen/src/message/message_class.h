/**
 * @file message_class.h
 * @author Feo
 * @date 01/10/2018
 * @brief
 */

#ifndef MESSAGEN_MESSAGE_CLASS_H
#define MESSAGEN_MESSAGE_CLASS_H

#include "message/class_field.h"

class message_class {
public:
    message_class();
    ~message_class();

    void name(const std::string& name) noexcept { _name = name; }

    void add_field(class_field *field) noexcept;

private:
    std::string                     _name;
    std::vector<class_field *>      _fields;

};

#endif /* MESSAGEN_MESSAGE_CLASS_H */
