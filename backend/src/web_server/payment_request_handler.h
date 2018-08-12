/**
 * @file payment_request_handler.h
 * @author Feo
 * @date 12/08/2018
 * @brief
 */

#ifndef BACKEND_PAYMENT_REQUEST_HANDLER_H
#define BACKEND_PAYMENT_REQUEST_HANDLER_H

#include <engine.h>

namespace backend {

    class payment_request_handler : public engine::http_request_handler {
    public:
        FW_DECLARE_SMARTPOINTERS(payment_request_handler)
        FW_DELETE_ALL_DEFAULT_EXCEPT_CTOR(payment_request_handler)

        payment_request_handler();
        virtual ~payment_request_handler();

        engine::http_response::sptr handle(const engine::http_request::sptr& request) noexcept final;

    private:

    };

}

#endif /* BACKEND_PAYMENT_REQUEST_HANDLER_H */
