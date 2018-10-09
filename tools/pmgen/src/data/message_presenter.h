/**
 * @file message_presenter.h
 * @author Feo
 * @date 01/10/2018
 * @brief
 */

#ifndef PMGEN_MESSAGE_PRESENTER_H
#define PMGEN_MESSAGE_PRESENTER_H

#include "data/field_presenter.h"

class message_presenter final {
public:
    STL_DECLARE_SMARTPOINTERS(message_presenter)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(message_presenter)

    using field_vector_type = std::vector<const field_presenter *>;

    message_presenter();
    ~message_presenter() = default;

    const std::string& name() const noexcept { return _name; }
    void name(const std::string& name) noexcept { _name = name; }

    void add_field(const field_presenter *field) noexcept;
    const field_vector_type& fields() const noexcept { return _fields; }

private:
    std::string                     _name;
    field_vector_type               _fields;

};

#endif /* PMGEN_MESSAGE_PRESENTER_H */
