/**
 * @file json_page.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_JSON_PAGE_H
#define ENGINE_JSON_PAGE_H

#include "context/web/page/web_page.h"

namespace engine {

    class json_page final : public web_page {
    public:
        STL_DECLARE_SMARTPOINTERS(json_page)
        STL_DELETE_ALL_DEFAULT(json_page)

        explicit json_page(const web_view::sptr& layout) noexcept;
        virtual ~json_page() = default;

    private:

    };

}

#endif /* PROJECT_JSON_PAGE_H */
