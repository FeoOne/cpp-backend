/**
 * @file application.h
 * @author Feo
 * @date 05/10/2018
 * @brief
 */

#ifndef PMGEN_APPLICATION_H
#define PMGEN_APPLICATION_H

#include <stl.h>

#include "main/command_line_argument_parser.h"

class application {
public:
    STL_DECLARE_SMARTPOINTERS(application)
    STL_DELETE_ALL_DEFAULT(application)

    explicit application(int argc, char **argv) noexcept;
    ~application() = default;

    static int start(int argc, char **argv) noexcept;

private:
    command_line_argument_parser::uptr      _argument_parser;

    int start() noexcept;

};


#endif /* PMGEN_APPLICATION_H */
