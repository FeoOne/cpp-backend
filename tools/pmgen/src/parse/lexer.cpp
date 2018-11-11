/**
 * @file lexer.cpp
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#include "parse/lexer.h"

bool lexer::generate(const std::string& content) noexcept
{
    if (!_generator->process(content)) {
        std::cout << "Failed to lex: " << content << std::endl;
        return false;
    }

    return true;
}
