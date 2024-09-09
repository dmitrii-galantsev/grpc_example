find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(absl REQUIRED)

# Set the path to gRPC's abseil installation
set(absl_DIR ${gRPC_DIR}/../absl)

# Protobuf/Grpc source files
set(PROTO_FILES
    text_update.proto
)

# Add Library target with protobuf sources
add_library(text_update SHARED ${PROTO_FILES})
target_link_libraries(text_update
        protobuf::libprotobuf
        gRPC::grpc++
        gRPC::grpc++_reflection
)
target_include_directories(text_update PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Compile protobuf and grpc files in text_update target to cpp
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET text_update LANGUAGE cpp)
protobuf_generate(TARGET text_update LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
