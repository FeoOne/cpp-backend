/**
 * @file uv_ex.h
 * @author Feo
 * @date 20/08/2018
 * @brief
 */

#ifndef GROOT_UV_EX_H
#define GROOT_UV_EX_H

#include <uv.h>

namespace groot {

    union network_handle {
        uv_handle_t     handle;
        uv_stream_t     stream;
        uv_tcp_t        tcp;
        uv_udp_t        udp;
    };

}

#endif /* GROOT_UV_EX_H */
