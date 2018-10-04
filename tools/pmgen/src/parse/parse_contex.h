/**
 * @file parse_contex.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_PARSE_CONTEX_H
#define PMGEN_PARSE_CONTEX_H

#include <stl.h>

#include "data/class_presenter.h"

class parse_contex {
public:
    using message_vector_type = std::vector<const class_presenter *>;

    parse_contex();
    ~parse_contex();

    const std::string& ns() const noexcept { return  _namespace; }
    void ns(const std::string& ns) noexcept { _namespace = ns; }

    u32 opcode_offset() const noexcept { return _opcode_offset; }
    void opcode_offset(u32 offset) noexcept { _opcode_offset = offset; }

    void commit_message(const class_presenter *message) noexcept { _messages.push_back(message); }
    const message_vector_type& messages() const noexcept { return _messages; }

private:
    std::string                         _namespace;

    message_vector_type                 _messages;

    u32                                 _opcode_offset;

};

#endif /* PMGEN_PARSE_CONTEX_H */
