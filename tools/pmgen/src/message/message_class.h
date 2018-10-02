/**
 * @file message_class.h
 * @author Feo
 * @date 01/10/2018
 * @brief
 */

#ifndef PMGEN_MESSAGE_CLASS_H
#define PMGEN_MESSAGE_CLASS_H

#include "message/class_field.h"

class message_class {
public:
    using field_vector_type = std::vector<const class_field *>;

    message_class();
    ~message_class();

    const std::string& name() const noexcept { return _name; }
    void name(const std::string& name) noexcept { _name = name; }

    void commit_field(const class_field *field) noexcept;
    const field_vector_type& fields() const noexcept { return _fields; }

private:
    std::string                     _name;
    field_vector_type               _fields;

};

#endif /* PMGEN_MESSAGE_CLASS_H */
