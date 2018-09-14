/**
 * @file worker_broke_down.h
 * @author Feo
 * @date 14/09/2018
 * @brief
 */

#ifndef ROCKET_WORKER_BROKE_DOWN_H
#define ROCKET_WORKER_BROKE_DOWN_H

#include "task/task.h"
#include "work/work_context.h"

namespace rocket {

    class worker_broken_task : public groot::crucial<task, worker_broken_task> {
    public:
        GR_DECLARE_SMARTPOINTERS(worker_broken_task)
        GR_DELETE_ALL_DEFAULT_EXCEPT_CTOR(worker_broken_task)

        explicit worker_broken_task(work_context::key_type context_key) noexcept : _context_key { context_key } {}
        virtual ~worker_broken_task() = default;

        work_context::key_type context_key() const noexcept { return _context_key; }

    private:
        work_context::key_type      _context_key;

    };

}

#endif /* ROCKET_WORKER_BROKE_DOWN_H */
