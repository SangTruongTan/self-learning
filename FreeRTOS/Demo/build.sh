#!/bin/bash

PROG_NAME="$(basename -- "${BASH_SOURCE[0]}")"
PROG_PATH="$(dirname $(readlink -f -- "${BASH_SOURCE[0]}"))"

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

echo "PROG_PATH=$PROG_PATH"

ECHO_HIGHLIGHT "Script path ==> $PROG_PATH" "BLUE"

install_freertos_enviroment

make -C $PROG_PATH
