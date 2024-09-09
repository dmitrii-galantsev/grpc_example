cmake_minimum_required(VERSION 3.10)
project(TextUpdateGRPC)

set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

set(PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/text_update.proto
)

add_library(text_update_proto
    ${PROTO_FILES}
)

target_link_libraries(text_update_proto
    PUBLIC
    protobuf::libprotobuf
    gRPC::grpc++
)

target_include_directories(text_update_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET text_update_proto LANGUAGE cpp)
protobuf_generate(TARGET text_update_proto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

add_executable(server src/server.cpp)
target_link_libraries(server PRIVATE text_update_proto)

add_executable(client src/client.cpp)
target_link_libraries(client PRIVATE text_update_proto)
