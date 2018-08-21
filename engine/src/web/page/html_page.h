/**
 * @file html_page.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_HTML_PAGE_H
#define ENGINE_HTML_PAGE_H

#include "web/page/web_page.h"

namespace engine {

    class html_page final : public web_page {
    public:
        FW_DECLARE_SMARTPOINTERS(html_page)
        FW_DELETE_ALL_DEFAULT(html_page)

        explicit html_page(const web_view::sptr& layout) noexcept;
        virtual ~html_page() = default;

    private:

    };

}

#endif /* ENGINE_HTML_PAGE_H */
