#!/usr/bin/env bash

CC=${CC:-clang}
CXX=${CXX:-clang++}

clean() {
    rm -rf build
    rm -rf .cache
}

build() {
    cmake -B build \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_PREFIX_PATH=/opt/grpc_clang/
}

clean
build
