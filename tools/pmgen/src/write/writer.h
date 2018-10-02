/**
 * @file writer.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_WRITER_H
#define PMGEN_WRITER_H

#include "parse/parser.h"

class writer {
public:
    writer();
    ~writer();

    void write(const std::string& path, parser& p) noexcept;

private:

};

#endif /* PMGEN_WRITER_H */
