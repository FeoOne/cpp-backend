/**
 * @file web_page.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "context/web/page/web_page.h"

namespace rocket {

    web_page::web_page(const web_view::sptr& layout) noexcept :
            _layout { layout }
    {

    }

}
