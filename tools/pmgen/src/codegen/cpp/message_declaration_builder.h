/**
 * @file message_declaration_builder.h
 * @author Feo
 * @date 03/10/2018
 * @brief
 */

#ifndef PMGEN_HEADER_BUILDER_H
#define PMGEN_HEADER_BUILDER_H

#include "parse/parsing_context.h"
#include "codegen/component_builder.h"
#include "codegen/cpp/building_context.h"

class message_declaration_builder final : public component_builder {
public:
    STL_DECLARE_SMARTPOINTERS(message_declaration_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(message_declaration_builder)

    explicit message_declaration_builder(building_context *build_context,
                                         const parsing_context *parse_context) noexcept;

    virtual ~message_declaration_builder() = default;

    std::string build() const noexcept final;

private:
    building_context *          _build_context;
    const parsing_context *     _parse_context;

};

#endif /* PMGEN_HEADER_BUILDER_H */
