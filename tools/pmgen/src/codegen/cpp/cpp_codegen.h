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

    cpp_codegen() = default;
    virtual ~cpp_codegen() = default;

    /**
     *
     * @param parser
     * @return Pair where first element is file name and second is content.
     */
    std::map<std::string, std::string> generate(parse_processor *parser) noexcept final;

private:

};

#endif /* PMGEN_CPP_CODEGEN_H */
