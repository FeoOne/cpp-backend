/**
 * @file handler_builder.h
 * @author Feo
 * @date 07/10/2018
 * @brief
 */

#ifndef PMGEN_HANDLER_BUILDER_H
#define PMGEN_HANDLER_BUILDER_H

#include "parse/parsing_context.h"
#include "codegen/component_builder.h"
#include "codegen/cpp/building_context.h"

class handler_declaration_builder final : public component_builder {
public:
    STL_DECLARE_SMARTPOINTERS(handler_declaration_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(handler_declaration_builder)

    explicit handler_declaration_builder(building_context *build_context,
                                         const parsing_context *parse_context) noexcept;

    virtual ~handler_declaration_builder() = default;

    std::string build() const noexcept final;

private:
    building_context *          _build_context;
    const parsing_context *     _parse_context;

};

#endif /* PMGEN_HANDLER_BUILDER_H */
