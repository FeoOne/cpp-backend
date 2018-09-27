/**
 * @file view.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ROCKET_VIEW_H
#define ROCKET_VIEW_H

#include <groot.h>

namespace rocket {

    class view_template {
    public:
        GR_DECLARE_SMARTPOINTERS(view_template)
        GR_DELETE_ALL_DEFAULT(view_template)

        explicit view_template(std::string key, size_t start_pos, size_t end_pos) noexcept :
                _key { key },
                _start_pos { start_pos },
                _end_pos { end_pos }
        {
        }

        ~view_template() = default;

        const std::string& get_key() const noexcept { return _key; }
        size_t get_start_pos() const noexcept { return _start_pos; }
        size_t get_count() const noexcept { return _end_pos - _start_pos; }

    private:
        std::string             _key;
        size_t                  _start_pos;
        size_t                  _end_pos;

    };

    class web_view {
    public:
        GR_DECLARE_SMARTPOINTERS(web_view)
        GR_DELETE_ALL_DEFAULT(web_view)

        explicit web_view(std::string&& content) noexcept;
        ~web_view();

        const std::string& compile_and_get_body() noexcept;

        void set_argument(const std::string& key, const std::string& value) noexcept;
        void set_argument(const std::string& key, const web_view::sptr& view) noexcept;

    private:
        class argument {
        public:
            GR_DECLARE_SMARTPOINTERS(argument)
            GR_DELETE_ALL_DEFAULT(argument)

            enum class type_t {
                STRING,
                VIEW,
            };

            explicit argument(const std::string& value) noexcept :
                    _type { type_t::STRING },
                    _view { nullptr },
                    _value { value }
            {
            }
            explicit argument(const web_view::sptr& view) noexcept :
                    _type { type_t::VIEW },
                    _view { view },
                    _value { "" }
            {
            }

            type_t get_type() const noexcept { return _type; }

            const std::string& get_value() const noexcept { return _value; }
            web_view::sptr get_view() const noexcept { return _view; }

        private:
            type_t      _type;

            web_view::sptr      _view;
            std::string         _value;

        };

        std::string                                         _content;
        std::vector<view_template::sptr>                    _templates;
        std::unordered_map<std::string, argument::sptr>     _arguments;

        void process() noexcept;
        void compile() noexcept;

    };

}

#endif /* PROJECT_VIEW_H */
