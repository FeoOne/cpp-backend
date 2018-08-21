/**
 * @file uv_ex.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef FRAMEWORK_UV_EX_H
#define FRAMEWORK_UV_EX_H

#include <uv.h>

namespace framework {

    union network_handle {
        uv_handle_t     handle;
        uv_stream_t     stream;
        uv_tcp_t        tcp;
        uv_udp_t        udp;
    };

}

#endif /* FRAMEWORK_UV_EX_H */
