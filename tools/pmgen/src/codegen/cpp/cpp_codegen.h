/**
 * @file cpp_codegen.h
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#ifndef PMGEN_CPP_CODEGEN_H
#define PMGEN_CPP_CODEGEN_H

#include "codegen/codegen.h"

class cpp_codegen : public codegen {
public:
    STL_DECLARE_SMARTPOINTERS(cpp_codegen)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(cpp_codegen)

    cpp_codegen();
    virtual ~cpp_codegen() = default;

    std::string generate(parse_processor *parser) noexcept final;

private:

};

#endif /* PMGEN_CPP_CODEGEN_H */
