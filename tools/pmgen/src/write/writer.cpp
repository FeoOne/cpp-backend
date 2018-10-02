/**
 * @file writer.cpp
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#include "write/tpl.h"
#include "parse/parse_contex.h"

#include "write/writer.h"

writer::writer()
{

}

writer::~writer()
{

}

void writer::write(const std::string& path, parser& p) noexcept
{
    auto header_tpl { new tpl("../../../tools/pmgen/templates/header.txt") };

    {
        std::string headerguard { p.contex().ns() };
        std::transform(headerguard.begin(), headerguard.end(), headerguard.begin(), std::toupper);
        header_tpl->replace(tpl::template_headerguard, headerguard);
    }

    for (auto message: p.contex().messages()) {
        auto class_tpl { new tpl("../../../tools/pmgen/templates/class.txt") };
    }

    
}
