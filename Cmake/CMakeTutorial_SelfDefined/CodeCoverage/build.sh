#! /bin/bash

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

DIR=$(script_dir)

ECHO_HIGHLIGHT "Script path ==> $DIR" "BLUE"

CONFIGURE="cmake -DCMAKE_BUILD_TYPE=Debug -S $DIR -B $DIR/out/build"
BUILD="cmake --build $DIR/out/build --target CodeCoverage_coverage_gcovr CodeCoverage_coverage_lcov"

configure_cmake "$CONFIGURE"
build_cmake "$BUILD"

if [[ ! -d $DIR/coverages ]]
then
    ECHO_HIGHLIGHT "$DIR/coverages does not exist. Create coverages folder." "BLUE"
    mkdir $DIR/coverages
fi
rsync -ah --progress $DIR/out/build/CodeCoverage_coverage_gcovr $DIR/coverages/CodeCoverage_coverage_gcovr
rsync -ah --progress $DIR/out/build/CodeCoverage_coverage_lcov $DIR/coverages/CodeCoverage_coverage_lcov

ECHO_HIGHLIGHT "BUILD SUCCESSFULLY" "LINE" "GREEN"
