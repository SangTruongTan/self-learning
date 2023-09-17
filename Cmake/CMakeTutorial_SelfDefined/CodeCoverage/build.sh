#! /bin/bash

PROG_NAME="$(basename -- "${BASH_SOURCE[0]}")"
PROG_PATH="$(dirname $(readlink -f -- "${BASH_SOURCE[0]}"))"

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

ECHO_HIGHLIGHT "Script path ==> $PROG_PATH" "BLUE"

CONFIGURE="cmake -DCMAKE_BUILD_TYPE=Debug -S $PROG_PATH -B $PROG_PATH/out/build"
BUILD="cmake --build $PROG_PATH/out/build --target CodeCoverage_coverage_gcovr CodeCoverage_coverage_lcov"

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

if [[ ! -d $PROG_PATH/coverages ]]
then
    ECHO_HIGHLIGHT "$PROG_PATH/coverages does not exist. Create coverages folder." "BLUE"
    mkdir $PROG_PATH/coverages
fi
rsync -ah --progress $PROG_PATH/out/build/CodeCoverage_coverage_gcovr $PROG_PATH/coverages/CodeCoverage_coverage_gcovr
EXIT_CODE=$?
if [[ $EXIT_CODE != "0" ]] ; then
    return $EXIT_CODE
fi
rsync -ah --progress $PROG_PATH/out/build/CodeCoverage_coverage_lcov $PROG_PATH/coverages/CodeCoverage_coverage_lcov
EXIT_CODE=$?
if [[ $EXIT_CODE != "0" ]] ; then
    return $EXIT_CODE
fi

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"
