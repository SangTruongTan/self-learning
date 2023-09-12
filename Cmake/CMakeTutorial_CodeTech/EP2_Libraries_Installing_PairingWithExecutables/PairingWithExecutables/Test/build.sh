#! /bin/bash

PROG_NAME="$(basename -- "${BASH_SOURCE[0]}")"
PROG_PATH="$(dirname $(readlink -f -- "${BASH_SOURCE[0]}"))"

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

ECHO_HIGHLIGHT "Script path ==> $PROG_PATH" "BLUE"

ECHO_HIGHLIGHT "Build libraries" "CYAN"
LIB_CONFIGURE="cmake -S $PROG_PATH/../AdderLib -B $PROG_PATH/../AdderLib/out/build -DCMAKE_INSTALL_PREFIX=$PROG_PATH/library/"
LIB_BUILD="cmake --build $PROG_PATH/../AdderLib/out/build --target install"

configure_cmake "$LIB_CONFIGURE"
build_cmake "$LIB_BUILD"

ECHO_HIGHLIGHT "Build Top CMakeLists.txt"
CONFIGURE="cmake -S $PROG_PATH -B $PROG_PATH/out/build"
BUILD="cmake --build $PROG_PATH/out/build"

configure_cmake "$CONFIGURE"
build_cmake "$BUILD"

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"
