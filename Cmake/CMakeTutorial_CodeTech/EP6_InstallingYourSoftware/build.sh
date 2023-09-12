#! /bin/bash

PROG_NAME="$(basename -- "${BASH_SOURCE[0]}")"
PROG_PATH="$(dirname $(readlink -f -- "${BASH_SOURCE[0]}"))"

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

ECHO_HIGHLIGHT "Script path ==> $PROG_PATH" "BLUE"

CONFIGURE="cmake -S $PROG_PATH -B $PROG_PATH/out/build -DCMAKE_INSTALL_PREFIX=$PROG_PATH/library"
BUILD="cmake --build $PROG_PATH/out/build --target install"

configure_cmake "$CONFIGURE"
build_cmake "$BUILD"

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"
