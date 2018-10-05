/**
 * @file codegen.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_WRITER_H
#define PMGEN_WRITER_H

#include "parse/parse_processor.h"

class codegen {
public:
    codegen();
    virtual ~codegen() = default;

    virtual std::string generate(parse_processor *parser) noexcept = 0;

private:

};

#endif /* PMGEN_WRITER_H */
