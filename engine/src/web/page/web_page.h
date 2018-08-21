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
        FW_DECLARE_SMARTPOINTERS(web_page)
        FW_DELETE_ALL_DEFAULT(web_page)

        explicit web_page(const web_view::sptr& layout) noexcept;
        virtual ~web_page() = default;



    private:
        web_view::sptr      _layout;

    };

}

#endif /* ENGINE_WEB_PAGE_H */
