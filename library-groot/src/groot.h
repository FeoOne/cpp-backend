/**
 * @file framework.h
 * @author Feo
 * @date 09/08/2018
 * @brief
 */

#ifndef GROOT_FRAMEWORK_H
#define GROOT_FRAMEWORK_H

#include <set>
#include <list>
#include <array>
#include <stack>
#include <deque>
#include <atomic>
#include <thread>
#include <limits>
#include <cassert>
#include <fstream>
#include <iostream>
#include <functional>
#include <condition_variable>

#include "util/crucial.h"
#include "util/optional.h"

#include "main/tools.h"

#include "time/time.h"

#include "scalar/string.h"
#include "scalar/numeric.h"

#include "logger/log_manager.h"

#include "memory/memory.h"

#include "config/config.h"
#include "config/command_line_option_processor.h"

#include "network/network.h"
#include "network/endpoint.h"

#include "external/uv_ex.h"
#include "external/glib_ex.h"

#endif /* GROOT_FRAMEWORK_H */
