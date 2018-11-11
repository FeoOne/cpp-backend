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
    class object_pool final {
    public:
        STL_DECLARE_SMARTPOINTERS(object_pool<T>)
        STL_DELETE_ALL_DEFAULT_EXCEPT_CTOR(object_pool)

        using value_type = T;
        using pointer_type = T *;

        object_pool() = default;
        ~object_pool() { free_all(); }

        pointer_type acquire() noexcept {
            pointer_type object { nullptr };
            if (_objects.empty()) {
                auto mem { memory::aligned_alloc<void>(sizeof(value_type)) };
                if (mem != nullptr) {
                    object = new (mem) value_type;
                }
                if (object == nullptr) {
                    abort();
                }
            } else {
                object = _objects.front();
                _objects.pop();
                if (object == nullptr) {
                    abort();
                }
            }
            return object;
        }

        void release(pointer_type object) noexcept {
            _objects.push(object);
        }

        void free_all() noexcept {
            while (!_objects.empty()) {
                auto object { _objects.front() };
                object->~value_type();
                memory::free(object);

                _objects.pop();
            }
        }

    private:
        std::queue<pointer_type>    _objects;

    };

}

#endif /* STL_OBJECT_POOL_H */
