/**
 * @file field_builder.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_FIELD_BUILDER_H
#define PMGEN_FIELD_BUILDER_H

#include <stl.h>

#include <string>

class field_builder {
public:
    explicit field_builder(field_builder *prev) noexcept;
    ~field_builder() = default;

    const std::string& name() const noexcept { return _name; }

    void set_name(const std::string& name) noexcept;
    void set_type(const std::string& type) noexcept;

    std::string build() noexcept;

private:
    field_builder *     _prev;
    std::string         _content;
    std::string         _name;

};

#endif /* PMGEN_FIELD_BUILDER_H */
