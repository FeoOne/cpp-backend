/**
 * @file socket.cpp
 * @author Feo
 * @date 10/08/2018
 * @brief
 */

#include <fcntl.h>

#include "network/socket.h"

namespace engine {

    void socket::non_blocking(bool mode) const noexcept
    {
        int flags = fcntl(_descriptor, F_GETFL, 0);
        if (flags != -1) {
            flags = mode ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
            if (fcntl(_descriptor, F_SETFL, flags) != 0) {
                logwarn("Failed to set blocking mode (%d, %s).", _descriptor, FW_FORMAT_BOOL(mode));
            }
        } else {
            logwarn("Failed to get blocking mode (%d).", _descriptor);
        }
    }

    bool socket::non_blocking() const noexcept
    {
        bool result { false };
        int flags = fcntl(_descriptor, F_GETFL, 0);
        if (flags != -1) {
            result = ((flags & O_NONBLOCK) == O_NONBLOCK);
        }
        return result;
    }

}
