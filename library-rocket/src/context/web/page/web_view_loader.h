/**
 * @file web_view_loader.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ROCKET_WEB_VIEW_LOADER_H
#define ROCKET_WEB_VIEW_LOADER_H

#include "main/rocket_consts.h"
#include "context/web/page/web_view.h"

namespace rocket {

    class web_view_loader {
    public:
        GR_DECLARE_SMARTPOINTERS(web_view_loader)
        GR_DELETE_ALL_DEFAULT(web_view_loader)

        explicit web_view_loader(const std::string_view& root_path) noexcept;
        ~web_view_loader();

        web_view::sptr load(const std::string& filename) noexcept;

    private:
        std::string_view                                    _root_path;
        std::unordered_map<std::string, std::string>        _cache;

    };

}

#endif /* ROCKET_WEB_VIEW_LOADER_H */
