/**
 * @file contex.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "parse/parse_contex.h"

parse_contex::parse_contex() :
        _namespace { "" },
        _messages {},
        _opcode_offset { 0 }
{
}

parse_contex::~parse_contex()
{
}
