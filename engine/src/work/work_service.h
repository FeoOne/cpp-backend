/**
 * @file execution_service.h
 * @author Feo
 * @date 11/08/2018
 * @brief
 */

#ifndef ENGINE_EXECUTION_SERVICE_H
#define ENGINE_EXECUTION_SERVICE_H

#include "event/event_recipient.h"

namespace engine {

    class work_service {
    public:
        FW_DECLARE_SMARTPOINTERS(work_service)
        FW_DELETE_ALL_DEFAULT(work_service)
        FW_CRUCIAL_BASE_DEFINITION()

        virtual ~work_service() = default;

    protected:
        explicit work_service(const event_recipient::sptr& recipient) noexcept;

        event_recipient::sptr get_recipient() const noexcept { return _recipient; }

    private:
        event_recipient::sptr      _recipient;

    };



}

#endif /* ENGINE_EXECUTION_SERVICE_H */
