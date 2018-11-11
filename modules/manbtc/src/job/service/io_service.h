/**
 * @file io_service.h
 * @author Feo
 * @date 06/11/2018
 * @brief
 */

#ifndef MANBTC_IO_SERVICE_H
#define MANBTC_IO_SERVICE_H

#include <pmp.h>
#include <engine.h>

namespace manbtc {

    class io_service final : public stl::crucial<engine::work_service, io_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(io_service)
        STL_DELETE_ALL_DEFAULT(io_service)

        explicit io_service(const stl::setting& config,
                            engine::task_router *router,
                            const engine::work_service_delegate *delegate) noexcept;

        virtual ~io_service() = default;

        void setup() noexcept final;
        void reset() noexcept final;

    private:

    };

}

#endif /* MANBTC_IO_SERVICE_H */
