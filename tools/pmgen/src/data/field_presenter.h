//
// Created by Feo on 01/10/2018.
//

#ifndef PMGEN_FIELD_PRESENTER_H
#define PMGEN_FIELD_PRESENTER_H

#include "data/field_attribute_presenter.h"

class field_presenter {
public:
    STL_DECLARE_SMARTPOINTERS(field_presenter)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(field_presenter)

    using attribute_vector_type = std::vector<const field_attribute_presenter *>;

    field_presenter();
    ~field_presenter() = default;

    const std::string& name() const noexcept { return _name; }
    void name(const std::string& name) noexcept { _name = name; }

    const std::string& type() const noexcept { return _type; }
    void type(const std::string& type) noexcept { _type = type; }

    int length() const noexcept { return _length; }
    void length(int length) noexcept { _length = length; }

    bool is_array() const noexcept { return _is_array; }
    void is_array(bool is_array) noexcept { _is_array = is_array; }

    void add_attribute(field_attribute_presenter *attribute) noexcept;
    const attribute_vector_type& attributes() const noexcept { return _attributes; }

private:
    std::string                     _name;
    std::string                     _type;
    bool                            _is_array;
    int                             _length;
    attribute_vector_type           _attributes;

};

#endif /* PMGEN_FIELD_PRESENTER_H */
