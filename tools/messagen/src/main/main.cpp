/**
 * @file main.cpp
 * @author Feo
 * @date 30/09/2018
 * @brief
 */

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <streambuf>

#include "main/lexertk.h"

int main(int argc, char **argv)
{
    const char *filepath = argv[1];

    std::ifstream file { filepath };
    std::string content { (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() };

    lexertk::generator generator;

    if (!generator.process(content)) {
        std::cout << "Failed to lex: " << content << std::endl;
        return EXIT_FAILURE;
    }

    lexertk::helper::bracket_checker bc;
    bc.process(generator);
    if (!bc.result()) {
        std::cout << "Failed Bracket Checker!" << std::endl;
        return 1;
    }

    lexertk::helper::dump(generator);

    return EXIT_SUCCESS;
}
