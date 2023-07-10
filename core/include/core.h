//
// Created by MikoG on 07.07.2023.
//

#ifndef EVO_CORE_H
#define EVO_CORE_H

#ifdef WIN64
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <arpa/inet.h>
#  include <netinet/in.h>
#  include <sys/socket.h>
#  include <sys/un.h>
#endif

namespace core {
    typedef char                  int8_t;
    typedef unsigned char       u_int8_t;
    typedef short                int16_t;
    typedef unsigned short     u_int16_t;
    typedef int                  int32_t;
    typedef unsigned int       u_int32_t;
    typedef long long            int64_t;
    typedef unsigned long long u_int64_t;
    typedef float              float32_t;
    typedef double             float64_t;
    typedef long double       float128_t;
    typedef void                  void_t;
    typedef bool                     bit;
    typedef u_int32_t             size_t;

    namespace pointer_types {
        typedef int8_t     *          string_t;
        typedef u_int8_t   *        u_string_t;
        typedef int16_t    *   pointer16_int_t;
        typedef u_int16_t  * u_pointer16_int_t;
        typedef int32_t    *   pointer32_int_t;
        typedef u_int32_t  * u_pointer32_int_t;
        typedef int64_t    *   pointer64_int_t;
        typedef u_int64_t  * u_pointer64_int_t;
        typedef float32_t  * pointer32_float_t;
        typedef float64_t  * pointer64_float_t;
        typedef float128_t *pointer128_float_t;
        typedef void_t     *         pointer_t;
        typedef bit        *     pointer_bit_t;
    }

    namespace socket_types {
        #ifdef WIN64
            typedef SOCKET          sock_bus;
            typedef core::int32_t   sock_len;
        #else
            typedef core::int32_t   sock_bus;
            typedef socklen_t       sock_len;
        #endif

        typedef sockaddr            sock_raw;
        typedef sockaddr_in        sock_ipv4;
        typedef sockaddr_in6       sock_ipv6;

        namespace pointer_types {
            typedef sock_bus  * pointer_sock_bus;
            typedef sock_len  * pointer_sock_len;
            typedef sock_ipv4 *pointer_sock_ipv4;
            typedef sock_ipv6 *pointer_sock_ipv6;
            typedef sock_raw  * pointer_sock_raw;
        }

        namespace defines {
            const core::int32_t tcp_stream   = SOCK_STREAM;
            const core::int32_t udp_stream   = SOCK_DGRAM;
            const core::int32_t ipv4_inet    = AF_INET;
            const core::int32_t ipv6_inet    = AF_INET6;
            const core::int32_t tcp_protocol = IPPROTO_TCP;
            const core::int32_t udp_protocol = IPPROTO_UDP;
            const core::int32_t tcp_queue    = 512;
            const core::int32_t ipv4_client  = 0xa1;
            const core::int32_t ipv4_server  = 0xa2;
            const core::int32_t ipv6_client  = 0xa3;
            const core::int32_t ipv6_server  = 0xa4;
        }

        namespace socket_errno {
            const core::u_int32_t sock_bus_init_errno        = 0xb1;
            const core::u_int32_t sock_bus_bind_errno        = 0xb2;
            const core::u_int32_t sock_bus_connect_tcp_errno = 0xb3;
            const core::u_int32_t sock_bus_accept_tcp_errno  = 0xb4;
            const core::u_int32_t sock_bus_send_tcp_errno    = 0xb5;
            const core::u_int32_t sock_bus_recv_tcp_errno    = 0xb6;
            const core::u_int32_t sock_bus_send_udp_errno    = 0xb7;
            const core::u_int32_t sock_bus_recv_udp_errno    = 0xb8;
            const core::u_int32_t sock_api_nullptr_errno     = 0xb9;
            const core::u_int32_t sock_api_win_wsa_errno     = 0xba;
            const core::u_int32_t sock_api_appointment_errno = 0xbb;
        }
    }

    namespace filesystem {
        namespace fs_errno {
            const core::u_int32_t fs_file_ok          =  0x0;
            const core::u_int32_t fs_file_open_errno  = 0xd1;
            const core::u_int32_t fs_file_write_errno = 0xd2;
            const core::u_int32_t fs_file_read_errno  = 0xd3;
            const core::u_int32_t fs_create_dir_errno = 0xd4;
            const core::u_int32_t fs_remove_dir_errno = 0xd5;
            const core::u_int32_t fs_copy_file_errno  = 0xd6;
        }
    }
}

#endif //EVO_CORE_H
