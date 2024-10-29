#!/bin/bash
set -e

USER_UID=$(id -u "$(whoami)")
USER_GID=$(id -g "$(whoami)")

SCRIPTPATH="$(
    cd -- "$(dirname "$0")" >/dev/null 2>&1
    pwd -P
)"
DOCKER_DIR=$SCRIPTPATH/../pipeline/

docker build \
    --build-arg="UID=$USER_UID" \
    --build-arg="GID=$USER_GID" \
    --tag aes-pipeline-box \
    "$DOCKER_DIR"

docker run \
    --volume "$SCRIPTPATH/..:/work" \
    --workdir "/work" \
    aes-pipeline-box "$@"
