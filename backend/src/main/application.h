/**
 * @file application.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef BACKEND_APPLICATION_H
#define BACKEND_APPLICATION_H

#include <engine.h>

namespace backend {

    class application : public engine::application {
    public:
        FW_DECLARE_SMARTPOINTERS(application)

        application() = default;
        virtual ~application() = default;

    private:

    };

}

#endif /* BACKEND_APPLICATION_H */
