#! /bin/bash

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

DIR=$(script_dir)

ECHO_HIGHLIGHT "Script path ==> $DIR" "BLUE"

CONFIGURE="cmake -S $DIR -B $DIR/out/build"
BUILD="cmake --build $DIR/out/build --target package"

configure_cmake "$CONFIGURE"
build_cmake "$BUILD"

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"
