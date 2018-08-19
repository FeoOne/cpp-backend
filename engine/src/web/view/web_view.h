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

    class web_view {
    public:
        FW_DECLARE_SMARTPOINTERS(web_view)
        FW_DELETE_ALL_DEFAULT(web_view)

        explicit web_view(std::string&& content) noexcept;
        ~web_view();

        void process() noexcept;

        const std::string& get_body() const noexcept { return _content; }

    private:
        std::string         _content;

    };

}

#endif /* PROJECT_VIEW_H */
