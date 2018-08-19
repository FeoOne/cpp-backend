/**
 * @file web_view_loader.cpp
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

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

//        auto it = _cache.find(filename);
//        if (it != _cache.end()) {
//            view = web_view::make_shared(it->second);
//        } else {
//            std::ifstream stream(path, std::ios::in);
//            if (stream.is_open()) {
//                stream.seekg(0, std::ios::end);
//                auto size = stream.tellg();
//                std::string content(static_cast<size_t>(size), ' ');
//                stream.seekg(0, std::ios::beg);
//                stream.read(&content[0], size);
//
//                view = web_view::make_shared(std::move(content));
//
//
//                _cache.insert({ filename, content });
//            } else {
//                logerror("Failed to load web view for with filename '%s'.", filename.c_str());
//            }
//        }

        return view;
    }

}
