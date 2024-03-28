#! /bin/bash

PROG_NAME="$(basename -- "${BASH_SOURCE[0]}")"
PROG_PATH="$(dirname $(readlink -f -- "${BASH_SOURCE[0]}"))"

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

ECHO_HIGHLIGHT "Script path ==> $PROG_PATH" "BLUE"

CONFIGURE="cmake -DCMAKE_BUILD_TYPE=Debug -S $PROG_PATH -B $PROG_PATH/build"
BUILD="cmake --build $PROG_PATH/build --target all_coverage_lcov --parallel 2"

configure_cmake "$CONFIGURE"
EXIT_CODE=$?
if [[ $EXIT_CODE != "0" ]] ; then
    return $EXIT_CODE
fi

build_cmake "$BUILD"
EXIT_CODE=$?
if [[ $EXIT_CODE != "0" ]] ; then
    return $EXIT_CODE
fi

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"
