/**
 * @file web_view_loader.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_VIEW_LOADER_H
#define ENGINE_WEB_VIEW_LOADER_H

#include "web/view/web_view.h"

namespace engine {

    class web_view_loader {
    public:
        FW_DECLARE_SMARTPOINTERS(web_view_loader)

        explicit web_view_loader(const std::string_view& root_path) noexcept;
        ~web_view_loader();

        web_view::sptr load(const std::string& filename) noexcept;

    private:
        std::string_view                                    _root_path;
        std::unordered_map<std::string, web_view::sptr>     _cache;

    };

}

#endif /* ENGINE_WEB_VIEW_LOADER_H */
