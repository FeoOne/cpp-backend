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
#include <tuple>
#include <stack>
#include <deque>
#include <chrono>
#include <mutex>
#include <atomic>
#include <thread>
#include <limits>
#include <cassert>
#include <utility>
#include <fstream>
#include <iostream>
#include <exception>
#include <functional>
#include <type_traits>
#include <condition_variable>

#include <inttypes.h>

#include "util/crucial.h"
#include "util/optional.h"
#include "util/object_pool.h"

#include "main/tools.h"
#include "main/platform.h"

#include "time/time.h"

#include "data/json.h"
#include "data/uuid.h"

#include "scalar/string.h"
#include "scalar/numeric.h"

#include "logger/log_manager.h"

#include "memory/memory.h"
#include "memory/fixed_memory_pool.h"
#include "memory/float_memory_pool.h"

#include "config/config.h"
#include "config/command_line_argument_parser.h"

#include "network/network.h"
#include "network/endpoint.h"

#include "hardware/hardware.h"

#include "crypto/checksum.h"

#include "external/uv_ex.h"
#include "external/glib_ex.h"

#endif /* GROOT_FRAMEWORK_H */
