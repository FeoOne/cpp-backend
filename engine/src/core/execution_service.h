/**
 * @file execution_service.h
 * @author Feo
 * @date 11/08/2018
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

        using key_type = size_t;

        virtual ~execution_service() = default;

        virtual key_type get_key() const noexcept = 0;

    protected:
        execution_service() = default;

    };

    template<typename T>
    class basic_execution_service : public execution_service {
    public:
        FW_DECLARE_SMARTPOINTERS(basic_execution_service<T>)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(basic_execution_service<T>)

        basic_execution_service() = default;
        virtual ~basic_execution_service() = default;

        key_type get_key() const noexcept final { return key(); }

        static key_type key() noexcept { return KEY; }

    private:
        static constexpr key_type KEY { FW_COUNTER };

    };

}

#endif /* ENGINE_EXECUTION_SERVICE_H */
