/**
 * @file parse_contex.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_PARSE_CONTEX_H
#define PMGEN_PARSE_CONTEX_H

#include <stl.h>

#include "data/message_presenter.h"

class parsing_context {
public:
    STL_DECLARE_SMARTPOINTERS(parsing_context)
    STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(parsing_context)

    using message_vector_type = std::vector<const message_presenter *>;

    parsing_context();
    ~parsing_context() = default;

    const std::string& ns() const noexcept { return  _namespace; }
    void ns(const std::string& ns) noexcept { _namespace = ns; }

    u32 opcode_offset() const noexcept { return _opcode_offset; }
    void opcode_offset(u32 offset) noexcept { _opcode_offset = offset; }

    const message_vector_type& messages() const noexcept { return _messages; }
    void add_message(const message_presenter *message) noexcept { _messages.push_back(message); }

private:
    std::string                         _namespace;
    u32                                 _opcode_offset;

    message_vector_type                 _messages;


};

#endif /* PMGEN_PARSE_CONTEX_H */
