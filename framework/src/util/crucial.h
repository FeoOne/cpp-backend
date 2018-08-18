/**
 * @file typed.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef FRAMEWORK_CRUCIAL_H
#define FRAMEWORK_CRUCIAL_H

#include <utility>

#include "main/tools.h"
#include "memory/memory.h"
#include "scalar/scalar.h"

#define FW_CRUCIAL_BASE_DEFINITION()                    \
    public:                                             \
        using key_type = framework::crucial_key_type;   \
    protected:                                          \
        static key_type _key_counter;                   \
    public:                                             \
        virtual key_type get_key() const noexcept = 0;

#define FW_CRUCIAL_BASE_DECLARATION(base)               \
    base::key_type base::_key_counter { 0 };

namespace framework {

    using crucial_key_type = size_t;

    template<typename Base, typename Derived>
    class crucial : public Base {
    public:
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(crucial)

        using key_type = typename Base::key_type;
        using base_type = Base;
        using derived_type = Derived;

        virtual ~crucial() = default;

        key_type get_key() const noexcept final { return key(); }

        static key_type key() noexcept {
            static const key_type k { Base::_key_counter++ };
            return k;
        }

    protected:
        crucial() = default;

        template<typename... Args>
        explicit crucial(Args&&... args) noexcept : base_type(std::forward<Args>(args)...) {}

    };

}

#endif /* FRAMEWORK_CRUCIAL_H */
