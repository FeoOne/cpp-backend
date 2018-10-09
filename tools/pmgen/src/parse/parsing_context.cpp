/**
 * @file contex.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "parse/parsing_context.h"

parsing_context::parsing_context() :
        _namespace { "" },
        _opcode_offset { 0 },
        _messages {}
{
}
