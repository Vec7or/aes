#!/bin/bash
CALLER_DIR=$(pwd)
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"¨
BUILD_PATH=$SCRIPTPATH/../build

mkdir -p $BUILD_PATH
cd $BUILD_PATH
cmake .. && cmake --build .
cd $CALLER_DIR