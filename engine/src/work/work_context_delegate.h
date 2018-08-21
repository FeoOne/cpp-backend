/**
 * @file work_context_delegate.h
 * @author Feo
 * @date 21/08/2018
 * @brief
 */

#ifndef ENGINE_WORK_CONTEXT_DELEGATE_H
#define ENGINE_WORK_CONTEXT_DELEGATE_H

#include <framework.h>

namespace engine {

    class work_loop;
    class work_service;

    class work_context_delegate {
    public:
        FW_DECLARE_SMARTPOINTERS(work_context_delegate)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(work_context_delegate)

        virtual ~work_context_delegate() = default;

        template<typename Loop>
        typename Loop::sptr get_own_loop() const noexcept {
            return std::static_pointer_cast<Loop>(get_loop());
        }

        template<typename Service>
        typename Service::sptr get_service() const noexcept {
            return std::static_pointer_cast<Service>(get_service(Service::key()));
        }

    protected:
        work_context_delegate() = default;

        virtual std::shared_ptr<work_loop> get_loop() const noexcept = 0;
        virtual std::shared_ptr<work_service> get_service(framework::crucial_key_type key) const noexcept = 0;

    };

}

#endif /* ENGINE_WORK_CONTEXT_DELEGATE_H */
