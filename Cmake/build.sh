#! /bin/bash

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

echo "GIT_DIRECTORY=$GIT_DIRECTORY"

source $GIT_DIRECTORY/Libraries/libraries.sh

DIR=$(script_dir)

echo $DIR

if [[ $1 == "install" ]]
then
    ECHO_HIGHLIGHT "Install neccessary dependencies" "LINE" "BLUE"
    sudo apt-get install libxss-dev libxxf86vm-dev libxkbfile-dev libxv-dev \
                 libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
                 mesa-common-dev libglu1-mesa-dev freeglut3-dev libglew-dev \
                 freeglut3-dev lcov clang-format gcovr
fi

Scripts=$(find $DIR/ -name "build.sh" -not -path "$DIR/build.sh")

# Run Scripts recursively
for i in $Scripts
do
    run_a_script $i
done

# Clean up
if [[ $1 == "clean" ]]
then
    ECHO_HIGHLIGHT "Clean up everything" "LINE" "RED" 
    git clean -dfX
    git submodule deinit --all
fi
