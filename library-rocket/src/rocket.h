/**
 * @file engine.h
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#ifndef ROCKET_ROCKET_H
#define ROCKET_ROCKET_H

#include "main/application.h"
#include "main/rocket_consts.h"

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
#include "web/task/http_request_task.h"
#include "web/task/http_response_task.h"
#include "web/task/ws_incoming_message_task.h"
#include "web/task/ws_outgoing_message_task.h"
#include "web/page/web_view_loader.h"
#include "web/page/web_view_manager.h"

#include "io/task/new_connection_task.h"
#include "io/task/message_request_task.h"
#include "io/task/message_response_task.h"
#include "io/task/close_connection_task.h"

#include "protocol/protocol_machine.h"

#endif /* ROCKET_ROCKET_H */
