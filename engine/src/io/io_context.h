/**
 * @file io_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_IO_CONTEXT_H
#define ENGINE_IO_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class io_context : public framework::crucial<work_context, io_context> {
    public:
        FW_DECLARE_SMARTPOINTERS(io_context)
        FW_DELETE_ALL_DEFAULT(io_context)

        explicit io_context(const framework::config_setting::sptr& config,
                            const task_router::sptr& router) noexcept;
        virtual ~io_context();

        void setup() noexcept final;
        void reset() noexcept final;

    };

}

#endif /* ENGINE_IO_CONTEXT_H */
