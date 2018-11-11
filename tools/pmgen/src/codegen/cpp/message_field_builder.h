/**
 * @file message_field_builder.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_FIELD_BUILDER_H
#define PMGEN_FIELD_BUILDER_H

#include <stl.h>

#include "data/field_presenter.h"
#include "codegen/component_builder.h"

class message_field_builder final : public component_builder {
public:
    STL_DECLARE_SMARTPOINTERS(message_field_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(message_field_builder)

    explicit message_field_builder(const field_presenter *field, const field_presenter *previous_field) noexcept;
    virtual  ~message_field_builder() = default;

    std::string build() const noexcept final;

private:
    const field_presenter *     _field;
    const field_presenter *     _previous_field;

};

#endif /* PMGEN_FIELD_BUILDER_H */
