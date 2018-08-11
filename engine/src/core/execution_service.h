/**
 * @file execution_service.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_SERVICE_H
#define ENGINE_EXECUTION_SERVICE_H

#include <framework.h>

namespace engine {

    class execution_service {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_service)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(execution_service)

        virtual ~execution_service() = default;

        virtual void create() noexcept = 0;
        virtual void destroy() noexcept = 0;

    protected:
        execution_service() = default;

    private:

    };

}

#endif /* ENGINE_EXECUTION_SERVICE_H */
