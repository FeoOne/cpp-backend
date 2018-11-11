/**
 * @file lexer.h
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#ifndef PMGEN_TOKENIZER_H
#define PMGEN_TOKENIZER_H

#include <stl.h>

#include "parse/lexertk.h"

class lexer final {
public:
    STL_DECLARE_SMARTPOINTERS(lexer)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(lexer)

    lexer() : _generator { std::make_unique<lexertk::generator>() } {}
    ~lexer() = default;

    bool generate(const std::string& content) noexcept;

    lexertk::generator *generator() noexcept { return _generator.get(); }

private:
    std::unique_ptr<lexertk::generator>     _generator;

};

#endif /* PMGEN_TOKENIZER_H */
