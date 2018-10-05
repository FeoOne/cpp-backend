/**
 * @file field_builder.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_FIELD_BUILDER_H
#define PMGEN_FIELD_BUILDER_H

#include <stl.h>

class field_builder {
public:
    STL_DECLARE_SMARTPOINTERS(field_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(field_builder)

    explicit field_builder(const field_builder::sptr& prev) noexcept;
    ~field_builder() = default;

    const std::string& name() const noexcept { return _name; }

    void set_name(const std::string& name) noexcept;
    void set_type(const std::string& type) noexcept;

    std::string build() noexcept;

private:
    field_builder::sptr     _prev;
    std::string             _content;
    std::string             _name;

};

#endif /* PMGEN_FIELD_BUILDER_H */
