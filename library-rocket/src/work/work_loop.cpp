/**
 * @file execution_loop.cpp
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#include "work/work_loop.h"

namespace rocket {

    work_loop::work_loop(const task_queue::sptr& queue, task_handler *handler) noexcept :
            _queue { queue },
            _handler { handler }
    {
    }

}
