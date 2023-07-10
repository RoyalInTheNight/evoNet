cmake_minimum_required(VERSION 3.24)
project(evo)

set(CMAKE_CXX_STANDARD 17)

set(SOCKET_LIB core/src/socket/socket.cpp)
set(FS_LIB core/src/filesystem/filesystem.cpp)

add_library(fs   STATIC ${FS_LIB})
add_library(sock STATIC ${SOCKET_LIB})

target_link_libraries(fs stdc++fs)
target_link_libraries(sock fs ws2_32)

add_executable(main main.cpp)
add_executable(client client.cpp)

target_link_libraries(main sock fs)
target_link_libraries(client sock fs)