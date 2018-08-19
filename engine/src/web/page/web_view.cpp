/**
 * @file view.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include "web/page/web_view.h"

namespace engine {

    web_view::web_view(std::string&& content) noexcept :
            _content { std::move(content) }
    {

    }

    web_view::~web_view()
    {

    }

    void web_view::process() noexcept
    {

    }

}
