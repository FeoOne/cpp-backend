/**
 * @file db_service.h
 * @author Feo
 * @date 10/11/2018
 * @brief
 */

#ifndef ENGINE_DB_SERVICE_H
#define ENGINE_DB_SERVICE_H

#include "work/service/work_service.h"

namespace engine {

    class db_service final : public stl::crucial<work_service, db_service> {
    public:
        STL_DECLARE_SMARTPOINTERS(db_service)
        STL_DELETE_ALL_DEFAULT(db_service)

        explicit db_service(const stl::setting& config,
                            task_router *router,
                            const work_service_delegate *delegate) noexcept;

        virtual ~db_service();

        void setup() noexcept final;
        void reset() noexcept final;

    private:
        void handle_db_response_task(engine::basic_task *base_task) noexcept;

    };

}

#endif /* ENGINE_DB_SERVICE_H */
