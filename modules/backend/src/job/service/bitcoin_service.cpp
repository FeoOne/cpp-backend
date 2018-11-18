/**
 * @file bitcoin_service.cpp
 * @author Feo
 * @date 18/11/2018
 * @brief
 */

#include "main/backend_consts.h"
#include "job/service/bitcoin_rpc_service.h"

#include "job/service/bitcoin_service.h"

#define EX_10M_TIMER_DELAY          1000
#define EX_10M_TIMER_REPEAT         60000

#define EX_FEE_WAIT_BLOCK_COUNT     2

namespace backend {

    bitcoin_service::bitcoin_service(const stl::setting &config,
                                     engine::task_router *router,
                                     const engine::work_service_delegate *delegate) noexcept :
            crucial(config, router, delegate),
            _10m_timer { engine::timer::make_unique() },
            _fee_wait_block_count { 0 },
            _estimated_fee { 0 }
    {
    }

    // virtual
    bitcoin_service::~bitcoin_service()
    {
    }

    void bitcoin_service::setup() noexcept
    {
        config().lookup_int32<size_t>(consts::config::key::bitcoin_fee_wait_blocks,
                                      &_fee_wait_block_count,
                                      EX_FEE_WAIT_BLOCK_COUNT);

        _10m_timer->setup(delegate()->loop<engine::job_loop>()->loop(),
                          EX_10M_TIMER_DELAY,
                          EX_10M_TIMER_REPEAT,
                          std::bind(&bitcoin_service::on_10m_timer, this));
        _10m_timer->start();
    }

    void bitcoin_service::reset() noexcept
    {
        _10m_timer->stop();
    }

    void bitcoin_service::on_10m_timer() noexcept
    {
        _estimated_fee = BITCOIN_RPC_SERVICE->get_estimated_fee(_fee_wait_block_count);
    }

}

#undef EX_FEE_WAIT_BLOCK_COUNT

#undef EX_10M_TIMER_REPEAT
#undef EX_10M_TIMER_DELAY
