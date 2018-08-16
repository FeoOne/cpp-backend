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

    class io_work_context : public work_context {
    public:
        FW_DECLARE_SMARTPOINTERS(io_work_context)
        FW_DELETE_ALL_DEFAULT(io_work_context)

        io_work_context();
        virtual ~io_work_context();

        void start() noexcept final;
        void stop() noexcept final;

    private:


    };

}

#endif /* ENGINE_IO_CONTEXT_H */
