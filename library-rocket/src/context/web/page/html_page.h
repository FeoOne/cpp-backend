/**
 * @file html_page.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_HTML_PAGE_H
#define ROCKET_HTML_PAGE_H

#include "context/web/page/web_page.h"

namespace rocket {

    class html_page final : public web_page {
    public:
        GR_DECLARE_SMARTPOINTERS(html_page)
        GR_DELETE_ALL_DEFAULT(html_page)

        explicit html_page(const web_view::sptr& layout) noexcept;
        virtual ~html_page() = default;

    private:

    };

}

#endif /* ROCKET_HTML_PAGE_H */
