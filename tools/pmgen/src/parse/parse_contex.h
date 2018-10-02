/**
 * @file parse_contex.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_PARSE_CONTEX_H
#define PMGEN_PARSE_CONTEX_H

#include "message/message_class.h"

class parse_contex {
public:
    using message_vector_type = std::vector<const message_class *>;

    parse_contex();
    ~parse_contex();

    const std::string& ns() const noexcept { return  _namespace; }
    void ns(const std::string& ns) noexcept { _namespace = ns; }

    void commit_message(const message_class *message) noexcept { _messages.push_back(message); }
    const message_vector_type& messages() const noexcept { return _messages; }

private:
    std::string                         _namespace;

    message_vector_type                 _messages;

};

#endif /* PMGEN_PARSE_CONTEX_H */
