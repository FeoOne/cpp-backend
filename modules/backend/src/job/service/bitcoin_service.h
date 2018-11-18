/**
 * @file bitcoin_service.h
 * @author Feo
 * @date 18/11/2018
 * @brief
 */

#ifndef BACKEND_BITCOIN_SERVICE_H
#define BACKEND_BITCOIN_SERVICE_H

#include <engine.h>

#define BITCOIN_SERVICE     delegate()->service<bitcoin_service>()

namespace backend {

    class bitcoin_service : public stl::crucial<engine::work_service, bitcoin_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(bitcoin_service)
        STL_DELETE_ALL_DEFAULT(bitcoin_service)

        explicit bitcoin_service(const stl::setting& config,
                                 engine::task_router *router,
                                 const engine::work_service_delegate *delegate) noexcept;

        virtual ~bitcoin_service();

        void setup() noexcept final;
        void reset() noexcept final;

        s64 estimated_fee() const noexcept { return _estimated_fee; }

    private:
        engine::timer::uptr         _10m_timer;

        size_t                      _fee_wait_block_count;

        s64                         _estimated_fee;

        void on_10m_timer() noexcept;
    };

}

#endif /* BACKEND_BITCOIN_SERVICE_H */
