//
// Created by MikoG on 07.07.2023.
//

#ifndef EVO_SOCKET_H
#define EVO_SOCKET_H

#ifdef UNIX_ROOT_SERVER_SOCKET
#  include "unix_socket.h"
#endif
#  include "../filesystem/filesystem.h"
#  include "../core.h"

#  include <vector>

using file               = Filesystem::filesystem;
namespace socket_types   = core_types::socket_types;
namespace socket_pointer = core_types::socket_types::pointer_types;
namespace socket_defines = core_types::socket_types::defines;
namespace socket_errno   = core_types::socket_types::socket_errno;

namespace ipv4_data {
    typedef struct sock_ipv4_data {
        socket_types::sock_bus             bus;
        socket_pointer::pointer_sock_ipv4 ipv4;
        socket_pointer::pointer_sock_len   len;

        union {
            core_types::u_int64_t address;
            core_types::u_int32_t  offset;
        };

        core_types::u_int32_t       flags;
        core_types::bit      cache_status;
        core_types::bit      block_status;
        core_types::u_int32_t    protocol;
        core_types::u_int32_t appointment;
    } sock_ipv4;
}

namespace ipv6_data {
    typedef struct sock_ipv6_data {
        socket_types::sock_bus             bus;
        socket_pointer::pointer_sock_ipv4 ipv6;
        socket_pointer::pointer_sock_len   len;

        union {
            core_types::u_int64_t address;
            core_types::u_int32_t  offset;
        };

        core_types::u_int32_t       flags;
        core_types::bit      cache_status;
        core_types::bit      block_status;
        core_types::u_int32_t    protocol;
        core_types::u_int32_t appointment;
    } sock_ipv6;
}

namespace Socket {
    class socket {
    private:
        core_types::u_int32_t last_socket_errno;
        std::vector<std::string>   cache_buffer;

    public:
        ipv4_data::sock_ipv4 *new_sock_ipv4();
        ipv4_data::sock_ipv4 *new_sock_ipv4(ipv4_data::sock_ipv4 *);
        ipv4_data::sock_ipv4 *new_sock_ipv4(ipv4_data::sock_ipv4 &);

        ipv6_data::sock_ipv6 *new_sock_ipv6();
        ipv6_data::sock_ipv6 *new_sock_ipv6(ipv6_data::sock_ipv6 *);
        ipv6_data::sock_ipv6 *new_sock_ipv6(ipv6_data::sock_ipv6 &);

        core_types::void_t ipv4_set_settings(ipv4_data::sock_ipv4 *, core_types::int32_t, core_types::u_int32_t, core_types::u_int32_t);
        core_types::void_t ipv6_set_settings(ipv6_data::sock_ipv6 *, core_types::int32_t, core_types::u_int32_t, core_types::u_int32_t);

        core_types::void_t ipv4_init_socket(ipv4_data::sock_ipv4 *, core_pointer::string_t, core_types::u_int16_t, core_types::u_int32_t);
        core_types::void_t ipv6_init_socket(ipv6_data::sock_ipv6 *, core_pointer::string_t, core_types::u_int16_t);

        core_types::void_t ipv4_bind_socket(ipv4_data::sock_ipv4 *);
        core_types::void_t ipv6_bind_socket(ipv6_data::sock_ipv6 *);

        core_types::void_t ipv4_socket_write(ipv4_data::sock_ipv4 *, std::string&);
        core_types::void_t ipv6_socket_write(ipv6_data::sock_ipv6 *, std::string&);

        core_types::void_t ipv4_socket_read(ipv4_data::sock_ipv4 *, std::string *, core_types::size_t);
        core_types::void_t ipv6_socket_read(ipv6_data::sock_ipv6 *, std::string *, core_types::size_t);

        core_types::void_t ipv4_socket_write_file(ipv4_data::sock_ipv4 *, const fs::path&);
        core_types::void_t ipv6_socket_write_file(ipv6_data::sock_ipv6 *, const fs::path&);

        core_types::void_t ipv4_socket_read_file(ipv4_data::sock_ipv4 *, const fs::path&);
        core_types::void_t ipv6_socket_read_file(ipv6_data::sock_ipv6 *, const fs::path&);

        core_types::void_t call_socket_exception(core_types::u_int32_t);
    };
}

#endif //EVO_SOCKET_H
