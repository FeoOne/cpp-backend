/**
 * @file io_context.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef ENGINE_IO_CONTEXT_H
#define ENGINE_IO_CONTEXT_H

#include "core/execution_context.h"

namespace engine {

    class io_context : public execution_context {
    public:
        io_context(const framework::config_setting::sptr& config);
        virtual ~io_context();

        FW_DELETE_DEFAULT_COPY_CTOR(io_context)
        FW_DELETE_DEFAULT_COPY_ASSIGN(io_context)

    private:

    };

}

#endif /* ENGINE_IO_CONTEXT_H */
