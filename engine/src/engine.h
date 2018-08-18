/**
 * @file engine.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "main/application.h"
#include "main/engine_const.h"

#include "job/job_loop.h"
#include "job/job_queue.h"
#include "job/job_context.h"

#include "system/system_loop.h"
#include "system/system_queue.h"
#include "system/system_context.h"

#include "web/webserver_loop.h"
#include "web/webserver_queue.h"
#include "web/webserver_context.h"
#include "web/service/http_service.h"
#include "web/service/websocket_service.h"

#endif /* ENGINE_ENGINE_H */
