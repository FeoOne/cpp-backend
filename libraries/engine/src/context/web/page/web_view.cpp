/**
 * @file view.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "context/web/page/web_view.h"

#define EX_SAFE_ARG_LENGTH      16
#define EX_APPROX_TPL_COUNT     16

namespace engine {

    web_view::web_view(std::string&& content) noexcept :
            _content { std::move(content) }
    {
        _templates.reserve(EX_APPROX_TPL_COUNT);
        process();
    }

    web_view::~web_view()
    {

    }

    const std::string& web_view::compile_and_get_body() noexcept
    {
        compile();
        return _content;
    }

    void web_view::set_argument(const std::string& key, const std::string& value) noexcept
    {
        _arguments.insert({ key, argument::make_shared(value) });
    }

    void web_view::set_argument(const std::string& key, const web_view::sptr& view) noexcept
    {
        _arguments.insert({ key, argument::make_shared(view) });
    }

    void web_view::process() noexcept
    {
        static const std::string open_brace { "{{" };
        static const std::string close_brace { "}}" };

        size_t pos { 0 };
        do {
            size_t start_pos;
            size_t end_pos;

            pos = _content.find(open_brace, pos);
            if (pos != std::string::npos) {
                start_pos = pos;
                pos = _content.find(close_brace, pos);
                if (pos != std::string::npos) {
                    end_pos = pos;
                    logassert(end_pos - start_pos <= EX_SAFE_ARG_LENGTH,
                            "To long template key. Looks like there is no trailing braces.");

                    auto key {
                        _content.substr(start_pos + open_brace.length(), end_pos - start_pos - open_brace.length())
                    };
                    auto tpl = view_template::make_shared(key, start_pos, end_pos + close_brace.length());

                    _templates.push_back(tpl);
                } else {
                    logerror("View has not close brace.");
                }
            }

        } while (pos != std::string::npos);
    }

    void web_view::compile() noexcept
    {
        size_t offset { 0 };
        for (auto& tpl: _templates) {
            auto it = _arguments.find(tpl->get_key());
            if (it != _arguments.end()) {
                auto arg = it->second;
                if (arg->get_type() == argument::type_t::VIEW && arg->get_view()) {
                    arg->get_view()->compile();
                    _content = _content.replace(tpl->get_start_pos() + offset,
                                                tpl->get_count(),
                                                arg->get_view()->_content);
                    offset += arg->get_view()->_content.length() - tpl->get_count();
                } else {
                    _content = _content.replace(tpl->get_start_pos() + offset,
                                                tpl->get_count(),
                                                arg->get_value());
                    offset += arg->get_value().length() - tpl->get_count();
                }
            } else {
                logerror("Failed to find value for argument '%s'.", tpl->get_key().c_str());
            }
        }
    }

}

#undef EX_SAFE_ARG_LENGTH
#undef EX_APPROX_TPL_COUNT
