//
// Created by Feo on 15/10/2018.
//

#ifndef PMGEN_MESSAGE_BUILDER_FIELD_BUILDER_H
#define PMGEN_MESSAGE_BUILDER_FIELD_BUILDER_H

#include <stl.h>

#include "data/field_presenter.h"
#include "codegen/component_builder.h"

class message_builder_field_builder final : public component_builder {
public:
    STL_DECLARE_SMARTPOINTERS(message_builder_field_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(message_builder_field_builder)

    explicit message_builder_field_builder(const field_presenter *field) noexcept;
    virtual  ~message_builder_field_builder() = default;

    std::string build() const noexcept final;

private:
    const field_presenter *     _field;

};

#endif /* PMGEN_MESSAGE_BUILDER_FIELD_BUILDER_H */
