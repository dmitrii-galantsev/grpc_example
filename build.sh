#!/usr/bin/env bash

set -eu

GRPC_ROOT=${GRPC_ROOT:-/opt/grpc}
if ! test -e "$GRPC_ROOT"; then
    tput bold setaf 3 bold; echo "[$GRPC_ROOT] does not exist, trying another dir"; tput sgr0
    GRPC_ROOT=/opt/grpc_clang
fi
if ! test -e "$GRPC_ROOT"; then
    tput bold setaf 1 bold; echo "[$GRPC_ROOT] does not exist"; tput sgr0
    exit 1
fi

clean() {
    rm -rf build
    rm -rf .cache
}

build() {
    tput setaf 6 bold; echo -e "configuring project.."; tput sgr0
    cmake -B build \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_PREFIX_PATH="$GRPC_ROOT"
    sleep 0.5
    tput setaf 6 bold; echo -e "building project.."; tput sgr0
    make -C build -j "$(nproc)"
}

clean
build
