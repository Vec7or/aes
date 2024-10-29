#!/bin/bash
# export CC=$(which clang)
# export CXX=$(which clang)

CALLER_DIR=$(pwd)
SCRIPTPATH="$(
    cd -- "$(dirname "$0")" >/dev/null 2>&1 || exit
    pwd -P
)"
BUILD_PATH=$SCRIPTPATH/../build

mkdir -p "$BUILD_PATH"
cd "$BUILD_PATH" || exit
cmake .. -G Ninja && cmake --build .
cd "$CALLER_DIR" || exit
