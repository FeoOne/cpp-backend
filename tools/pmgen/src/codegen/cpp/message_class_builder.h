/**
 * @file message_class_builder.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_CLASS_BUILDER_H
#define PMGEN_CLASS_BUILDER_H

#include "data/message_presenter.h"
#include "codegen/cpp/building_context.h"
#include "codegen/cpp/message_field_builder.h"
#include "codegen/cpp/message_builder_field_builder.h"

class message_class_builder final : public component_builder {
public:
    STL_DECLARE_SMARTPOINTERS(message_class_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(message_class_builder)

    explicit message_class_builder(building_context *build_context, const message_presenter *message) noexcept;
    virtual ~message_class_builder() = default;

    std::string build() const noexcept final;

private:
    building_context *              _build_context;
    const message_presenter *       _message;

};

#endif /* PMGEN_CLASS_BUILDER_H */
