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

    class execution_service {
    public:
        FW_DECLARE_SMARTPOINTERS(execution_service)
        FW_DELETE_ALL_DEFAULT(execution_service)
        FW_CRUCIAL_BASE_DEFINITION()

        virtual ~execution_service() = default;

    protected:
        explicit execution_service(const event_recipient::sptr& recipient) noexcept;

        event_recipient::sptr recipient() const noexcept { return _recipient; }

    private:
        event_recipient::sptr      _recipient;

    };



}

#endif /* ENGINE_EXECUTION_SERVICE_H */
