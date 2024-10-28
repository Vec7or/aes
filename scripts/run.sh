#!/bin/bash
CALLER_DIR=$(pwd)
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"¨
BUILD_PATH=$SCRIPTPATH/../build
EXECUTABLE_NAME=kica_aes

mkdir -p $BUILD_PATH
cd $BUILD_PATH
./$EXECUTABLE_NAME
cd $CALLER_DIR