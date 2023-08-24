#! /bin/bash

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

DIR=$(script_dir)

ECHO_HIGHLIGHT "Script path ==> $DIR" "BLUE"

ECHO_HIGHLIGHT "Build libraries" "CYAN"
LIB_CONFIGURE="cmake -S $DIR/../AdderLib -B $DIR/../AdderLib/out/build"
LIB_BUILD="cmake --build $DIR/../AdderLib/out/build"

configure_cmake "$LIB_CONFIGURE"
build_cmake "$LIB_BUILD"

ECHO_HIGHLIGHT "Build Top CMakeLists.txt"
CONFIGURE="cmake -S $DIR -B $DIR/out/build"
BUILD="cmake --build $DIR/out/build"

configure_cmake "$CONFIGURE"
build_cmake "$BUILD"

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"
