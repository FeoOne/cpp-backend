/**
 * @file web_page.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef ENGINE_WEB_PAGE_H
#define ENGINE_WEB_PAGE_H

#include "web/page/web_view.h"

namespace engine {

    class web_page {
    public:
        web_page(const web_view::sptr& root_view);
        ~web_page();

    private:

    };

}

#endif /* ENGINE_WEB_PAGE_H */
