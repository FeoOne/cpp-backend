/**
 * @file tpl.h
 * @author Feo
 * @date 02/10/2018
 * @brief
 */

#ifndef PMGEN_TPL_H
#define PMGEN_TPL_H

#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>

class tpl {
public:
    static constexpr std::string_view template_headerguard { "%HEADERGUARD%" };
    static constexpr std::string_view template_namespace { "%NAMESPACE%" };
    static constexpr std::string_view template_body { "%BODY%" };

    explicit tpl(const std::string& filepath) noexcept;
    ~tpl();

    const std::string content() const noexcept { return _content; }

    void replace(const std::string_view& pattern, const std::string& text) noexcept;

private:
    std::string         _content;

};

#endif /* PMGEN_TPL_H */
