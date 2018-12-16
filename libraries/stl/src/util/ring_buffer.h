/**
 * @file ring_buffer.h
 * @author Feo
 * @date 16/12/2018
 * @brief
 */

#ifndef STL_RING_BUFFER_H
#define STL_RING_BUFFER_H

#include <array>

namespace stl {

    template<typename T, size_t Size>
    class ring_buffer final {
    public:
        T& operator [](size_t index) noexcept {
            return _array[index & (Size - 1)];
        }

        size_t size() const noexcept { return _array.size(); }

    private:
        std::array<T, Size>     _array;

    };

}

#endif /* STL_RING_BUFFER_H */
