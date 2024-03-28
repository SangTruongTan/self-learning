#! /bin/bash

PROG_NAME="$(basename -- "${BASH_SOURCE[0]}")"
PROG_PATH="$(dirname $(readlink -f -- "${BASH_SOURCE[0]}"))"

GIT_PROG_PATHECTORY="$(git rev-parse --show-toplevel)"

echo "GIT_PROG_PATHECTORY=$GIT_PROG_PATHECTORY"

source $GIT_PROG_PATHECTORY/Libraries/libraries.sh

ECHO_HIGHLIGHT "Script path ==> $PROG_PATH" "BLUE"

# APT PACKAGES
CMAKE_PACKAGE="make cmake gcc g++ libxss-dev libxxf86vm-dev libxkbfile-dev
               libxv-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
               mesa-common-dev libglu1-mesa-dev freeglut3-dev libglew-dev \
               freeglut3-dev lcov clang-format gcovr"
FREERTOS_PACKAGE="make cmake gcc g++"
DOXYGEN_PACKAGE="doxygen graphviz"
FUNNYFARM_PACKAGE="libncurses5-dev"

# Intall packages.
if [[ $1 == "install" ]] ; then
    ECHO_HIGHLIGHT "Install neccessary dependencies" "LINE" "BLUE"
    ECHO_HIGHLIGHT "Run sudo apt update in advance." "BLUE"
    sudo apt-get update
    if [[ $2 == "cmake" ]] ; then
        sudo apt-get install -y $CMAKE_PACKAGE
    elif [[ $2 == "freertos" ]] ; then
        sudo apt-get install -y $FREERTOS_PACKAGE
    elif [[ $2 == "doxygen" ]] ; then
        sudo apt-get install -y $DOXYGEN_PACKAGE
    elif [[ $2 == "farm" ]] ; then
        sudo apt-get install -y $FUNNYFARM_PACKAGE
    elif [[ $2 == "all" ]] ; then
        sudo apt-get install -y $CMAKE_PACKAGE $FREERTOS_PACKAGE $DOXYGEN_PACKAGE $FUNNYFARM_PACKAGE
    fi
    return 0
fi

# Clean up
if [[ $1 == "clean" ]]
then
    ECHO_HIGHLIGHT "Clean up ignored files and submodules." "LINE" "RED"
    git clean -dfX
    git submodule deinit --all
    return 0
fi

# Initialize git submodules
if [[ $1 == "init" ]]
then
    ECHO_HIGHLIGHT "Initialize git submodules" "LINE" "BLUE"
    git submodule update --init --recursive
    return 0
fi

# Setup environment
if [[ $1 == "setup" ]] ; then
    if [[ $2 == "freertos" ]] ; then
        if [[ $3 == "arm" ]] ; then
            wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2 \
            -O $HOME/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2
            tar -xjvf $HOME/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2 -C $HOME
        elif [[ $3 == "amd" ]] ; then
            wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \
            -O $HOME/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
            tar -xjvf $HOME/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 -C $HOME
        fi
    elif [[ $2 == "google" ]] ; then
        if [[ -f "${GIT_PROG_PATHECTORY}/external/googletest/CMakeLists.txt" ]] ; then
            ECHO_HIGHLIGHT "googletest/CMakeLists.txt is found." "LINE" "GREEN"
            mkdir -p "${GIT_PROG_PATHECTORY}/external/googletest/build"
            cmake -S "${GIT_PROG_PATHECTORY}/external/googletest/" -B "${GIT_PROG_PATHECTORY}/external/googletest/build"
            if [[ $? != "0" ]] ; then
                ECHO_HIGHLIGHT "Failed to setup and generate CMake infrastructure." "LINE" "RED"
                return 1
            fi
            cmake --build "${GIT_PROG_PATHECTORY}/external/googletest/build"
            if [[ $? != "0" ]] ; then
                ECHO_HIGHLIGHT "Failed to build googletest binaries." "LINE" "RED"
                return 1
            fi
        else
            ECHO_HIGHLIGHT "googletest repository hasn't been initialized yet. Please update submodules." "LINE" "RED"
            return 1
        fi
    elif [[ $2 == "dlt" ]] ; then
        if [[ -f "${GIT_PROG_PATHECTORY}/external/dlt-daemon/CMakeLists.txt" ]] ; then
            ECHO_HIGHLIGHT "dlt-daemon/CMakeLists.txt is found." "LINE" "GREEN"
            mkdir -p "${GIT_PROG_PATHECTORY}/external/dlt-daemon/build"
            cmake -S "${GIT_PROG_PATHECTORY}/external/dlt-daemon/" -B "${GIT_PROG_PATHECTORY}/external/dlt-daemon/build"
            if [[ $? != "0" ]] ; then
                ECHO_HIGHLIGHT "Failed to setup and generate CMake infrastructure." "LINE" "RED"
                return 1
            fi
            cmake --build "${GIT_PROG_PATHECTORY}/external/dlt-daemon/build"
            if [[ $? != "0" ]] ; then
                ECHO_HIGHLIGHT "Failed to build dlt-daemon binaries." "LINE" "RED"
                return 1
            fi
        else
            ECHO_HIGHLIGHT "dlt-daemon repository hasn't been initialized yet. Please update submodules." "LINE" "RED"
            return 1
        fi
    fi
    return 0
fi

# Build
if [[ $1 == "build_cmake" ]] ; then
    ECHO_HIGHLIGHT "Build Cmake" "LINE" "YELLOW"
    Scripts=$(find $PROG_PATH/Cmake -name "build.sh" -not -path "$PROG_PATH/build.sh")
elif [[ $1 == "build_freertos" ]] ; then
    ECHO_HIGHLIGHT "Build FreeRTOS" "LINE" "YELLOW"
    Scripts=$(find $PROG_PATH/FreeRTOS -name "build.sh" ! -path "$PROG_PATH/build.sh" ! -path "$PROG_PATH/FreeRTOS/external/*" )
elif [[ $1 == "build_farm" ]] ; then
    ECHO_HIGHLIGHT "Build Funny Farm Project" "LINE" "YELLOW"
    Scripts=$(find $PROG_PATH/Cpp/FarmFunnyGame -name "build.sh" -not -path "$PROG_PATH/build.sh")
elif [[ $1 == "build_all" ]] ; then
    ECHO_HIGHLIGHT "Build all" "LINE" "YELLOW"
    Scripts=$(find $PROG_PATH -name "build.sh" ! -path "$PROG_PATH/build.sh" ! -path "$PROG_PATH/FreeRTOS/external/*" )
fi

# Run Scripts recursively
for i in $Scripts
do
    run_a_script $i
    EXIT_CODE=$?
    if [[ $EXIT_CODE != "0" ]] ; then
        ECHO_HIGHLIGHT "One of scripts was failed" "LINE" "RED"
        return $EXIT_CODE
    fi
done
