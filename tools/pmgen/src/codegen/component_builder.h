/**
 * @file component_builder.h
 * @author Feo
 * @date 07/10/2018
 * @brief
 */

#ifndef PMGEN_COMPONENT_BUILDER_H
#define PMGEN_COMPONENT_BUILDER_H

#include <stl.h>

class component_builder {
public:
    STL_DECLARE_SMARTPOINTERS(component_builder)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(component_builder)

    virtual ~component_builder() = default;

    virtual std::string build() const noexcept = 0;

protected:
    component_builder() = default;

};

#endif /* PMGEN_COMPONENT_BUILDER_H */
