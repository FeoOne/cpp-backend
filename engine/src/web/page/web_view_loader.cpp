/**
 * @file web_view_loader.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#include <glib.h>

#include "web/page/web_view_loader.h"

namespace engine {

    web_view_loader::web_view_loader(const std::string_view& root_path) noexcept :
            _root_path { root_path },
            _cache {}
    {
    }

    web_view_loader::~web_view_loader()
    {
    }

    web_view::sptr web_view_loader::load(const std::string& filename) noexcept
    {
        web_view::sptr  view { nullptr };
        std::string     path { std::string(_root_path) + "/" + filename };

        auto it = _cache.find(filename);
        if (it != _cache.end()) {
            std::string content(it->second);
            view = web_view::make_shared(std::move(content));
        } else {
            GError *error   { nullptr };
            gchar *buffer;
            gsize length;

            if (g_file_get_contents(path.c_str(), &buffer, &length, &error) == TRUE) {
                std::string content(buffer, length);
                g_free(buffer);
                view = web_view::make_shared(std::move(content));
            } else {
                logerror("Failed load page '%s': %s.", path.c_str(), error->message);
            }
        }

        return view;
    }

}
