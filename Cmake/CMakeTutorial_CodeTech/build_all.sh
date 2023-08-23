#! /bin/bash
echo "### Execute automatic script to build all Cmake project ###"

DIR="$( cd "$( dirname "$0" )" && pwd )"

echo $DIR

find $DIR/ -name "build.sh" -exec {} \;
