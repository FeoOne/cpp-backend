/**
 * @file system_context.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_SYSTEM_CONTEXT_H
#define ENGINE_SYSTEM_CONTEXT_H

#include "work/work_context.h"

namespace engine {

    class system_context : public framework::crucial<work_context, system_context> {
    public:
        FW_DECLARE_SMARTPOINTERS(system_context)
        FW_DELETE_ALL_DEFAULT(system_context)

        explicit system_context(const framework::config_setting::sptr& config,
                                const task_router::sptr& router) noexcept;
        virtual ~system_context();

        void setup() noexcept final;
        void reset() noexcept final;

    };

}

#endif /* ENGINE_SYSTEM_CONTEXT_H */
