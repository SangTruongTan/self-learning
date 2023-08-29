#! /bin/bash

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

echo "GIT_DIRECTORY=$GIT_DIRECTORY"

source $GIT_DIRECTORY/Libraries/libraries.sh

DIR=$(script_dir)

echo $DIR

Scripts=$(find $DIR/ -name "build.sh" -not -path "$DIR/build.sh")

# Run Scripts recursively
for i in $Scripts
do
    run_a_script $i
done
