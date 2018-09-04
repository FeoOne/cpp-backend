/**
 * @file main.cpp
 * @author Feo
 * @date 02/09/2018
 * @brief
 */

#include <groot.h>

#include "main/command_line_argument_parser.h"

using namespace tivan;

int main(int argc, char **argv)
{
    auto argument_parser { command_line_argument_parser::make_unique(argc, argv, "") };
    argument_parser->parse();

    std::ifstream stream { argument_parser->input_file().data() };
    std::string str((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    groot::json j = groot::json::parse(str);

    std::cout << j["namespace"] << std::endl;

    return 0;
}
