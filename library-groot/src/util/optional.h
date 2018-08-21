/**
 * @file optional.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef GROOT_OPTIONAL_H
#define GROOT_OPTIONAL_H

#include <utility>

namespace groot {

    template<typename T>
    class optional {
    public:
        using value_type = T;

        optional() : _value {}, _is_set { false } {}
        optional(const optional& other) noexcept : _value { other._value }, _is_set { other._is_set } {}
        optional(optional&& other) noexcept : _value { std::move(other._value) }, _is_set { other._is_set } {}
        explicit optional(const value_type& value) noexcept : _value { value }, _is_set { true } {}
        explicit optional(value_type&& value) noexcept : _value { std::move(value) }, _is_set { true } {}
        ~optional() = default;

        bool is_set() const noexcept { return _is_set; }

        value_type& value() noexcept { return _value; }
        void value(const value_type& v) { _value = v; _is_set = true; }
        void value(value_type&& v) { _value = std::move(v); _is_set = true; }

        value_type *pointer() noexcept {
            value_type *result { nullptr };
            if (_is_set) {
                result = &_value;
            }
            return result;
        }

        const value_type *pointer() const noexcept {
            value_type *result { nullptr };
            if (_is_set) {
                result = &_value;
            }
            return result;
        }

        void reset() noexcept { _is_set = false; }

    private:
        value_type      _value;
        bool            _is_set;

    };

}

#endif /* GROOT_OPTIONAL_H */
