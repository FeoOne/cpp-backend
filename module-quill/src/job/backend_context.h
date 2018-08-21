/**
 * @file n_context.h
 * @author Feo
 * @date 19/08/2018
 * @brief
 */

#ifndef BACKEND_BACKEND_CONTEXT_H
#define BACKEND_BACKEND_CONTEXT_H

#include <engine.h>

namespace backend {

    class backend_context : public engine::job_context {
    public:
        FW_DECLARE_SMARTPOINTERS(backend_context)
        FW_DELETE_ALL_DEFAULT(backend_context)

        explicit backend_context(const framework::config_setting::sptr& config,
                                     const engine::task_router::sptr& router) noexcept;
        virtual ~backend_context();

    private:
        void setup() noexcept final;
        void reset() noexcept final;

    };

}

#endif /* BACKEND_BACKEND_CONTEXT_H */
