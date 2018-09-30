/**
 * @file work_context_delegate.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ROCKET_WORK_CONTEXT_DELEGATE_H
#define ROCKET_WORK_CONTEXT_DELEGATE_H

#include <groot.h>

namespace rocket {

    class work_loop;
    class work_service;

    class work_service_delegate {
    public:
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(work_service_delegate)

        virtual ~work_service_delegate() = default;

        template<typename T>
        T *loop() const noexcept {
            return static_cast<T *>(get_loop_impl());
        }

        template<typename T>
        T *service() const noexcept {
            return static_cast<T *>(get_service_impl(T::key()));
        }

    protected:
        work_service_delegate() = default;

    private:
        virtual work_loop *get_loop_impl() const noexcept = 0;
        virtual work_service *get_service_impl(groot::crucial_key_type key) const noexcept = 0;

    };

}

#endif /* ROCKET_WORK_CONTEXT_DELEGATE_H */
