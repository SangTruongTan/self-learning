#! /bin/bash

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

DIR=$(script_dir)

ECHO_HIGHLIGHT "Script path ==> $DIR" "BLUE"

# apt-get install libxss-dev libxxf86vm-dev libxkbfile-dev libxv-dev libxrandr-dev libxinerama libxcursor libxi mesa-common-dev libglu1-mesa-dev freeglut3-dev

CONFIGURE="cmake -S $DIR -B $DIR/out/build"
BUILD="cmake --build $DIR/out/build"

configure_cmake "$CONFIGURE"
build_cmake "$BUILD"

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"

