//
// Created by MikoG on 07.07.2023.
//
#include "../../include/socket/socket.h"

ipv4_data::sock_ipv4 *Socket::socket::new_sock_ipv4() {
    ipv4_data::sock_ipv4 *tmp_sock = new ipv4_data::sock_ipv4();

    tmp_sock->ipv4 = new socket_types::sock_ipv4();
    tmp_sock->len  = new socket_types::sock_len();

    return tmp_sock;
}

ipv4_data::sock_ipv4 *Socket::socket::new_sock_ipv4(ipv4_data::sock_ipv4 *ipv4) {
    if (ipv4       == nullptr ||
        ipv4->ipv4 == nullptr ||
        ipv4->len  == nullptr) {
        last_socket_errno = socket_errno::sock_api_nullptr_errno;
        call_socket_exception(last_socket_errno);
    }

    ipv4_data::sock_ipv4 *tmp_sock = new ipv4_data::sock_ipv4();

    tmp_sock->bus  = ipv4->bus;
    tmp_sock->ipv4 = ipv4->ipv4;
    tmp_sock->len  = ipv4->len;

    return tmp_sock;
}

ipv4_data::sock_ipv4 *Socket::socket::new_sock_ipv4(ipv4_data::sock_ipv4 &ipv4) {
    if (ipv4.ipv4 == nullptr ||
        ipv4.len  == nullptr) {
        last_socket_errno = socket_errno::sock_api_nullptr_errno;
        call_socket_exception(last_socket_errno);
    }

    ipv4_data::sock_ipv4 *tmp_sock = new ipv4_data::sock_ipv4();

    tmp_sock->bus  = ipv4.bus;
    tmp_sock->ipv4 = ipv4.ipv4;
    tmp_sock->len  = ipv4.len;

    return tmp_sock;
}

core_types::void_t Socket::socket::ipv4_set_settings(ipv4_data::sock_ipv4 *ipv4_sock,
                                                     core_types::int32_t   stream_type,
                                                     core_types::u_int32_t protocol_type,
                                                     core_types::u_int32_t appointment) {
    if (ipv4_sock       == nullptr ||
        ipv4_sock->ipv4 == nullptr ||
        ipv4_sock->len  == nullptr) {
        last_socket_errno = socket_errno::sock_api_nullptr_errno;
        call_socket_exception(last_socket_errno);
    }

    #ifdef WIN64
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            last_socket_errno = socket_errno::sock_api_win_wsa_errno;
            call_socket_exception(last_socket_errno);
        }
    #endif

    ipv4_sock->appointment = appointment;
    ipv4_sock->protocol    = protocol_type;
    ipv4_sock->bus         = ::socket(socket_defines::ipv4_inet, stream_type, protocol_type);
   *ipv4_sock->len         = sizeof(*ipv4_sock->ipv4);

    #ifdef WIN64
        if (ipv4_sock->bus == INVALID_SOCKET) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #else
        if (ipv4_sock->bus < 0) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #endif
}

core_types::void_t Socket::socket::ipv4_init_socket(ipv4_data::sock_ipv4 *ipv4_sock,
                                                    core_pointer::string_t address,
                                                    core_types::u_int16_t  port,
                                                    core_types::u_int32_t  flags) {
    if (ipv4_sock       == nullptr ||
        ipv4_sock->ipv4 == nullptr ||
        ipv4_sock->len  == nullptr) {
        last_socket_errno = socket_errno::sock_api_nullptr_errno;
        call_socket_exception(last_socket_errno);
    }

    //inet_pton(socket_defines::ipv4_inet,
    //          address,
    //          &ipv4_sock->ipv4->sin_addr);
                     ipv4_sock->ipv4->sin_addr.S_un.S_addr = inet_addr(address);
                     ipv4_sock->ipv4->sin_port   = htons(port);
                     ipv4_sock->ipv4->sin_family = socket_defines::ipv4_inet;
                     ipv4_sock->flags            = flags;
}

core_types::void_t Socket::socket::ipv4_bind_socket(ipv4_data::sock_ipv4 *ipv4_sock) {
    if (ipv4_sock       == nullptr ||
        ipv4_sock->ipv4 == nullptr ||
        ipv4_sock->len  == nullptr) {
        last_socket_errno = socket_errno::sock_api_nullptr_errno;
        call_socket_exception(last_socket_errno);
    }

    #ifdef WIN64
        if (ipv4_sock->bus == INVALID_SOCKET) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #else
        if (ipv4_sock->bus < 0) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #endif

    core_types::int32_t result = 0;

    if (ipv4_sock->appointment == socket_defines::ipv4_server) {
        if (ipv4_sock->protocol == socket_defines::tcp_protocol) {
            result = ::bind(ipv4_sock->bus,
                            (const socket_pointer::pointer_sock_raw)ipv4_sock->ipv4,
                            *ipv4_sock->len);

            #ifdef WIN64
                if (result == SOCKET_ERROR) {
                    last_socket_errno = socket_errno::sock_bus_bind_errno;
                    call_socket_exception(last_socket_errno);
                }
            #else
                if (result < 0) {
                    last_socket_errno = socket_errno::sock_bus_bind_errno;
                    call_socket_exception(last_socket_errno);
                }
            #endif

            result = ::listen(ipv4_sock->bus, socket_defines::tcp_queue);

            #ifdef WIN64
                if (result == SOCKET_ERROR) {
                    last_socket_errno = socket_errno::sock_bus_bind_errno;
                    call_socket_exception(last_socket_errno);
                }
            #else
                if (result < 0) {
                    last_socket_errno = socket_errno::sock_bus_bind_errno;
                    call_socket_exception(last_socket_errno);
                }
            #endif

            ipv4_sock->bus = ::accept(ipv4_sock->bus,
                                      (const socket_pointer::pointer_sock_raw)ipv4_sock->ipv4,
                                      ipv4_sock->len);

            #ifdef WIN64
                if (ipv4_sock->bus == INVALID_SOCKET) {
                    last_socket_errno = socket_errno::sock_bus_init_errno;
                    call_socket_exception(last_socket_errno);
                }
            #else
                if (ipv4_sock->bus < 0) {
                    last_socket_errno = socket_errno::sock_bus_init_errno;
                    call_socket_exception(last_socket_errno);
                }
            #endif
        }

        else if (ipv4_sock->protocol == socket_defines::udp_protocol) {
            result = ::bind(ipv4_sock->bus,
                            (const socket_pointer::pointer_sock_raw)ipv4_sock->ipv4,
                            *ipv4_sock->len);

            #ifdef WIN64
                if (result == SOCKET_ERROR) {
                    last_socket_errno = socket_errno::sock_bus_bind_errno;
                    call_socket_exception(last_socket_errno);
                }
            #else
                if (result < 0) {
                    last_socket_errno = socket_errno::sock_bus_bind_errno;
                    call_socket_exception(last_socket_errno);
                }
            #endif
        }

        else {
            last_socket_errno = socket_errno::sock_api_appointment_errno;
            call_socket_exception(last_socket_errno);
        }
    }

    else if (ipv4_sock->appointment == socket_defines::ipv4_client) {
        if (ipv4_sock->protocol == socket_defines::tcp_protocol) {
            result = ::connect(ipv4_sock->bus,
                               (const socket_pointer::pointer_sock_raw)ipv4_sock->ipv4,
                               *ipv4_sock->len);

            #ifdef WIN64
                if (result == SOCKET_ERROR) {
                    last_socket_errno = socket_errno::sock_bus_connect_tcp_errno;
                    call_socket_exception(last_socket_errno);
                }
            #else
                if (result < 0) {
                    last_socket_errno = socket_errno::sock_bus_connect_tcp_errno;
                    call_socket_exception(last_socket_errno);
                }
            #endif
        }

        else if (ipv4_sock->protocol == socket_defines::udp_protocol);
        else {
            last_socket_errno = socket_errno::sock_api_appointment_errno;
            call_socket_exception(last_socket_errno);
        }
    }
}

core_types::void_t Socket::socket::ipv4_socket_write(ipv4_data::sock_ipv4 *ipv4_sock,
                                                     std::string          &data) {
    #ifdef WIN64
        if (ipv4_sock->bus == INVALID_SOCKET) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #else
        if (ipv4_sock->bus < 0) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #endif

    core_types::int32_t    result = 0;
    core_types::size_t     size = data.size();
    core_pointer::string_t point;

    while (size) {
        if (size >= __INT16_MAX__) {
            ipv4_sock->block_status = true;
            point = data.data();
        }

        if (ipv4_sock->protocol == socket_defines::tcp_protocol) {
            if (ipv4_sock->block_status) {
                result = ::send(ipv4_sock->bus,
                                point,
                                __INT16_MAX__,
                                (core_types::int32_t)ipv4_sock->flags);

                size -= __INT16_MAX__;
                point = &(*(point + __INT16_MAX__));
            }

            else if (!ipv4_sock->block_status) {
                result = ::send(ipv4_sock->bus,
                                data.c_str(),
                                size,
                                (core_types::int32_t)ipv4_sock->flags);

                size -= data.size();
            }

            if (result < 0) {
                last_socket_errno = socket_errno::sock_bus_send_tcp_errno;
                call_socket_exception(last_socket_errno);
            }
        }

        else if (ipv4_sock->protocol == socket_defines::udp_protocol) {
            if (ipv4_sock->appointment == socket_defines::ipv4_client) {
                if (ipv4_sock->block_status) {
                    result = ::sendto(ipv4_sock->bus,
                                      point,
                                      __INT16_MAX__,
                                      (core_types::int32_t)ipv4_sock->flags,
                                      (const socket_pointer::pointer_sock_raw)ipv4_sock->ipv4,
                                      *ipv4_sock->len);

                    size -= __INT16_MAX__;
                    point = &(*(point + __INT16_MAX__));
                }

                else if (!ipv4_sock->block_status) {
                    result = ::sendto(ipv4_sock->bus,
                                      data.c_str(),
                                      size,
                                      (core_types::int32_t)ipv4_sock->flags,
                                      (const socket_pointer::pointer_sock_raw)ipv4_sock->ipv4,
                                      *ipv4_sock->len);

                    size -= data.size();
                }

                if (result < 0) {
                    last_socket_errno = socket_errno::sock_bus_send_udp_errno;
                    call_socket_exception(last_socket_errno);
                }
            }

            else if (ipv4_sock->appointment == socket_defines::ipv4_server) {
                if (ipv4_sock->block_status) {
                    result = ::send(ipv4_sock->bus,
                                    point,
                                    __INT16_MAX__,
                                    (core_types::int32_t)ipv4_sock->flags);

                    size -= __INT16_MAX__;
                    point = &(*(point + __INT16_MAX__));
                }

                else if (!ipv4_sock->block_status){
                    result = ::send(ipv4_sock->bus,
                                    data.c_str(),
                                    size,
                                    (core_types::int32_t)ipv4_sock->flags);

                    size -= data.size();
                }

                if (result < 0) {
                    last_socket_errno = socket_errno::sock_bus_send_tcp_errno;
                    call_socket_exception(last_socket_errno);
                }
            }

            else {
                last_socket_errno = socket_errno::sock_api_appointment_errno;
                call_socket_exception(last_socket_errno);
            }
        }

        else {
            last_socket_errno = socket_errno::sock_api_appointment_errno;
            call_socket_exception(last_socket_errno);
        }
    }
}

core_types::void_t Socket::socket::ipv4_socket_read(ipv4_data::sock_ipv4 *ipv4_sock,
                                                    std::string          *data,
                                                    core_types::size_t    size) {
    #ifdef WIN64
        if (ipv4_sock->bus == INVALID_SOCKET) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #else
        if (ipv4_sock->bus < 0) {
            last_socket_errno = socket_errno::sock_bus_init_errno;
            call_socket_exception(last_socket_errno);
        }
    #endif

    core_types::int32_t   result = 0;
    core_types::u_int32_t __size = size;
    core_pointer::string_t buffer = new core_types::int8_t[__size];

    Filesystem::filesystem fs_tmp;

    do {
        if (data->size() > __INT16_MAX__) {
            cache_buffer.push_back(".1_" + std::to_string(data->size()) + ".cache");

            fs_tmp.write_file(cache_buffer.at(cache_buffer.size() - 1), data->data());
            data->clear();
        }

        if (ipv4_sock->protocol == socket_defines::tcp_protocol) {
            result = ::recv(ipv4_sock->bus,
                            buffer,
                            __size,
                            (core_types::int32_t)ipv4_sock->flags);

            *data += buffer;

            // utils_tmp.memory_clear(buffer);
        }

        else if (ipv4_sock->protocol == socket_defines::udp_protocol) {
            result = ::recvfrom(ipv4_sock->bus,
                                buffer,
                                __size,
                                (core_types::int32_t)ipv4_sock->flags,
                                (const socket_pointer::pointer_sock_raw)ipv4_sock->ipv4,
                                ipv4_sock->len);

            *data += buffer;

            // utils_tmp.memory_clear(buffer);
        }

        else {
            last_socket_errno = socket_errno::sock_api_appointment_errno;
            call_socket_exception(last_socket_errno);
        }
    } while (result != 0);
}

core_types::void_t Socket::socket::ipv4_socket_write_file(ipv4_data::sock_ipv4 *ipv4_sock,
                                                          const fs::path &path) {
    Filesystem::filesystem fs_tmp;

    std::string data = fs_tmp.read_file(path);
    ipv4_socket_write(ipv4_sock, data);
}

core_types::void_t Socket::socket::ipv4_socket_read_file(ipv4_data::sock_ipv4 *ipv4_sock,
                                                         const fs::path &path) {
    Filesystem::filesystem fs_tmp;

    std::string data;
    ipv4_socket_read(ipv4_sock, &data, __INT16_MAX__);

    if (cache_buffer.size() == 0)
        fs_tmp.write_file(path, data.data());

    else {
        std::string data2 = data;

        for (core_types::size_t i = 0; i < cache_buffer.size(); i++)
            data2 += fs_tmp.read_file(cache_buffer.at(i));

        data.clear();

        data = data2;
    }

    fs_tmp.write_file(path, data.data());
}

core_types::void_t Socket::socket::call_socket_exception(core_types::u_int32_t last_errno) {
    switch (last_errno) {
        case socket_errno::sock_api_appointment_errno:
            throw std::runtime_error("app");
        case socket_errno::sock_api_nullptr_errno:
            throw std::runtime_error("null");
        case socket_errno::sock_api_win_wsa_errno:
            throw std::runtime_error("win_wsa");
        case socket_errno::sock_bus_init_errno:
            throw std::runtime_error("init");
        case socket_errno::sock_bus_bind_errno:
            throw std::runtime_error("bind");
        case socket_errno::sock_bus_connect_tcp_errno:
            throw std::runtime_error("connect");
        case socket_errno::sock_bus_accept_tcp_errno:
            throw std::runtime_error("accept");
        case socket_errno::sock_bus_recv_tcp_errno:
            throw std::runtime_error("recv");
    }
}