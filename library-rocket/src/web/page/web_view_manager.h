/**
 * @file web_view_manager.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ROCKET_WEB_VIEW_MANAGER_H
#define ROCKET_WEB_VIEW_MANAGER_H

#include "web/page/web_view.h"

namespace rocket {

    class web_view_manager {
    public:
        GR_DECLARE_SMARTPOINTERS(web_view_manager)

        web_view_manager();
        ~web_view_manager();

        void preload(const std::string_view& key, const std::string& filename) noexcept;

    private:
        std::unordered_map<std::string_view, web_view::sptr>    _views;

    };

}

#endif /* ROCKET_WEB_VIEW_MANAGER_H */
