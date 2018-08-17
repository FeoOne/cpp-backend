//
// Created by Feo on 17/08/2018.
//

#include "main/engine_const.h"

#include "web/webserver_queue.h"

namespace engine {

    webserver_queue::webserver_queue() :
            task_queue(engine_const::DOMAIN_TASK_QUEUE_WEBSERVER)
    {

    }

}
