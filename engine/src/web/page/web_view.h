/**
 * @file view.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ENGINE_VIEW_H
#define ENGINE_VIEW_H

#include <framework.h>

namespace engine {

    class view_template {
    public:
        FW_DECLARE_SMARTPOINTERS(view_template)
        FW_DELETE_ALL_DEFAULT(view_template)

        explicit view_template(std::string_view key, size_t start_pos, size_t end_pos) noexcept :
                _key { key },
                _start_pos { start_pos },
                _end_pos { end_pos }
        {}

        ~view_template() = default;

    private:
        std::string_view        _key;
        size_t                  _start_pos;
        size_t                  _end_pos;

    };

    class web_view {
    public:
        FW_DECLARE_SMARTPOINTERS(web_view)
        FW_DELETE_ALL_DEFAULT(web_view)

        explicit web_view(std::string&& content) noexcept;
        ~web_view();

        const std::string& get_body() const noexcept { return _content; }

    private:
        std::string                         _content;
        std::vector<view_template::sptr>    _templates;

        void process() noexcept;

    };

}

#endif /* PROJECT_VIEW_H */
