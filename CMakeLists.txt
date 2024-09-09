cmake_minimum_required(VERSION 3.20)
project(TextUpdateGRPC LANGUAGES CXX)

option(CMAKE_VERBOSE_MAKEFILE "Enable verbose output" ON)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile commands for linters and autocompleters" ON)

set(CMAKE_CXX_STANDARD
    17
    CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED
    ON
    CACHE BOOL "")
set(CMAKE_CXX_EXTENSIONS
    OFF
    CACHE BOOL "")

add_subdirectory(protos)

add_executable(server src/server.cpp)
target_link_libraries(server PRIVATE text_update)

add_executable(client src/client.cpp)
target_link_libraries(client PRIVATE text_update)
