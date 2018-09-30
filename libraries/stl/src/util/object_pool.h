/**
 * @file object_pool.h
 * @author Feo
 * @date 24/09/2018
 * @brief
 */

#ifndef STL_OBJECT_POOL_H
#define STL_OBJECT_POOL_H

#include <queue>

#include "memory/memory.h"

namespace stl {

    template<typename T>
    class object_pool {
    public:
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(object_pool)

        using value_type = T;
        using pointer_type = T *;

        object_pool() = default;
        ~object_pool() = default;

        pointer_type acquire() noexcept {
            pointer_type object;
            if (_objects.empty()) {
                object = new(std::nothrow) value_type;
            } else {
                object = _objects.front();
                _objects.pop();
            }
            return object;
        }

        void release(pointer_type object) noexcept {
            _objects.push(object);
        }

    private:
        std::queue<pointer_type>    _objects;

    };

}

#endif /* STL_OBJECT_POOL_H */
