/**
 * @file merchandise.h
 * @author Feo
 * @date 06/11/2018
 * @brief
 */

#ifndef BACKEND_MERCHANDISE_H
#define BACKEND_MERCHANDISE_H

#include <engine.h>

namespace backend::data {

    class merchandise {
    public:
        STL_DELETE_ALL_DEFAULT(merchandise)
        STL_DECLARE_SMARTPOINTERS(merchandise)

        explicit merchandise(stl::uuid&& guid) noexcept :
                _guid { guid }
        {}

        ~merchandise() = default;

        const stl::uuid& guid() const noexcept { return _guid; }

    private:
        stl::uuid               _guid;

    };

}

#endif /* BACKEND_MERCHANDISE_H */
