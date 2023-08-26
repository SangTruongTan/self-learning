#! /bin/bash

GIT_DIRECTORY="$(git rev-parse --show-toplevel)"

source $GIT_DIRECTORY/Libraries/libraries.sh

DIR=$(script_dir)

rm -rf $DIR/out/*
