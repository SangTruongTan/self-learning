#!/bin/bash

PROG_NAME="$(basename -- "${BASH_SOURCE[0]}")"
PROG_PATH="$(dirname $(readlink -f -- "${BASH_SOURCE[0]}"))"

GIT_PROG_PATHECTORY="$(git rev-parse --show-toplevel)"

source $GIT_PROG_PATHECTORY/Libraries/libraries.sh

# Function definitions
function setup_arm_gcc()
{
    if [[ "$1" == "arm" ]] ; then
        ECHO_HIGHLIGHT "Setting up GCC ARM for ARM architecture.🍗" "GREEN"
        wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2 \
        -O $HOME/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2
        tar -xjvf $HOME/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2 -C $HOME
        return 0
    elif [[ "$1" == "amd" ]] ; then
        ECHO_HIGHLIGHT "Setting up GCC ARM for AMD architecture.🥠" "GREEN"
        wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \
        -O $HOME/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
        tar -xjvf $HOME/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 -C $HOME
        return 0
    else
        ECHO_HIGHLIGHT "--archtecture option needs to be specified.🥠" "RED"
        return 1
    fi
}

function setup_googletest()
{
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
}

function setup_dlt()
{
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
}

function display_help()
{
    ECHO_HIGHLIGHT "**************************************" "YELLOW"
    ECHO_HIGHLIGHT "Usage: script_name [option] [argument]" "YELLOW"
    ECHO_HIGHLIGHT "Description: Brief description of the script."
    ECHO_HIGHLIGHT
    ECHO_HIGHLIGHT "Options:"
    ECHO_HIGHLIGHT "  -h, --help                         Display this help message."
    ECHO_HIGHLIGHT "  -i, --init                         Init git submodules."
    ECHO_HIGHLIGHT "  --install          ins_arg         Specify the install argument."
    ECHO_HIGHLIGHT "  --setup            set_arg         Specify the setup argument."
    ECHO_HIGHLIGHT "  --architecture     arch_arg        Specify the architecture argument."
    ECHO_HIGHLIGHT "  --clean                            Clean up the repo."
    ECHO_HIGHLIGHT "  --build            build_arg       Specify the build argument."
    ECHO_HIGHLIGHT "  --parallel         par_arg         Specify the parallel argument."
    ECHO_HIGHLIGHT
    ECHO_HIGHLIGHT "Arguments:"
    ECHO_HIGHLIGHT "  ins_arg            [cmake|freertos|doxygen|farm|all]."
    ECHO_HIGHLIGHT "  set_arg            [freertos|google|dlt|all]."
    ECHO_HIGHLIGHT "  arch_arg           [arm|amd]."
    ECHO_HIGHLIGHT "  build_arg          [cmake|freertos|farm|all]."
    ECHO_HIGHLIGHT "  par_arg            Number of parallel jobs."
    ECHO_HIGHLIGHT "**************************************" "YELLOW"
}

# Unset all variables
unset init_value install_value setup_value architecture_value clean_value
unset build_value parallel_value
#Parsing arguments
while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    -i|--init)
        init_value=true
        shift 1
        ;;
    --install)
        if [[ -z "$2" ]] ; then
            ECHO_HIGHLIGHT "--install's value needs to be specified" "RED"
            return 1
        else
            install_value="$2"
            shift 2
        fi
        ;;
    --setup)
        if [[ -z "$2" ]] ; then
            ECHO_HIGHLIGHT "--setup's value needs to be specified" "RED"
            return 1
        else
            setup_value="$2"
            shift 2
        fi
        ;;
    --architecture)
        if [[ -z "$2" ]] ; then
            ECHO_HIGHLIGHT "--architecture's value needs to be specified" "RED"
            return 1
        else
            architecture_value="$2"
            shift 2
        fi
        ;;
    --clean)
        clean_value=true
        shift 1
        ;;
    --build)
        if [[ -z "$2" ]] ; then
            ECHO_HIGHLIGHT "--build's value needs to be specified" "RED"
            return 1
        else
            build_value="$2"
            shift 2
        fi
        ;;
    --parallel)
        if [[ -z "$2" ]] ; then
            ECHO_HIGHLIGHT "--parallel's value needs to be specified" "RED"
            return 1
        else
            if [[ $2 =~ ^[0-9]+$ ]] ; then
                parallel_value="$2"
                shift 2
            else
                ECHO_HIGHLIGHT "--parallel's value needs to be in number format" "RED"
                return 1
            fi
        fi
        ;;
    -h|--help)
        display_help
        return 0
        ;;
    *)
        ECHO_HIGHLIGHT "Invalid option: $key" "RED"
        shift
        ;;
  esac
done

# Print the values
echo "GIT_PROG_PATHECTORY=$GIT_PROG_PATHECTORY"

ECHO_HIGHLIGHT "Script path ==> $PROG_PATH" "BLUE"

ECHO_HIGHLIGHT "Number of Processors ==> $(nproc) 🥗🥗🥗" "GREEN"

# APT PACKAGES
CMAKE_PACKAGE="make cmake gcc g++ libxss-dev libxxf86vm-dev libxkbfile-dev
               libxv-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
               mesa-common-dev libglu1-mesa-dev freeglut3-dev libglew-dev \
               freeglut3-dev lcov clang-format gcovr"
FREERTOS_PACKAGE="make cmake gcc g++"
DOXYGEN_PACKAGE="doxygen graphviz"
FUNNYFARM_PACKAGE="libncurses5-dev"

# Specify the parallel jobs
if [[ -z "$parallel_value" ]] ; then
    NUMBER_OF_PARALLEL=$(nproc)
else
    NUMBER_OF_PARALLEL=$parallel_value
fi

ECHO_HIGHLIGHT "NUMBER_OF_PARALLEL=${NUMBER_OF_PARALLEL} ♋♋♋" "GREEN"

# Initialize git submodules
if [[ ! -z "$init_value" ]]
then
    ECHO_HIGHLIGHT "Initialize git submodules" "LINE" "BLUE"
    git submodule update --init --recursive
fi

# Intall packages.
if [[ ! -z "$install_value" ]] ; then
    ECHO_HIGHLIGHT "Install neccessary dependencies" "LINE" "BLUE"
    ECHO_HIGHLIGHT "Run sudo apt update in advance." "BLUE"
    sudo apt-get update
    if [[ "$install_value" == "cmake" ]] ; then
        ECHO_HIGHLIGHT "Installing CMake dependencies." "BLUE"
        sudo apt-get install -y $CMAKE_PACKAGE
    elif [[ "$install_value" == "freertos" ]] ; then
        ECHO_HIGHLIGHT "Installing FreeRTOS dependencies." "BLUE"
        sudo apt-get install -y $FREERTOS_PACKAGE
    elif [[ "$install_value" == "doxygen" ]] ; then
        ECHO_HIGHLIGHT "Installing Doxygen dependencies." "BLUE"
        sudo apt-get install -y $DOXYGEN_PACKAGE
    elif [[ "$install_value" == "farm" ]] ; then
        ECHO_HIGHLIGHT "Installing Funny Farm Project dependencies." "BLUE"
        sudo apt-get install -y $FUNNYFARM_PACKAGE
    elif [[ "$install_value" == "all" ]] ; then
        ECHO_HIGHLIGHT "Installing all dependencies." "BLUE"
        sudo apt-get install -y $CMAKE_PACKAGE $FREERTOS_PACKAGE $DOXYGEN_PACKAGE $FUNNYFARM_PACKAGE
    fi
fi

# Setup environment
if [[ ! -z "$setup_value" ]] ; then
    if [[ "$setup_value" == "freertos" ]] ; then
        ECHO_HIGHLIGHT "Setting up GCC ARM Tools." "LINE" "BLUE"
        setup_arm_gcc "$architecture_value"
        if [[ $? != "0" ]] ; then
            return 1
        fi
    elif [[ "$setup_value" == "google" ]] ; then
        ECHO_HIGHLIGHT "Setting up Google Test." "LINE" "BLUE"
        setup_googletest
        if [[ $? != "0" ]] ; then
            return 1
        fi
    elif [[ "$setup_value" == "dlt" ]] ; then
        ECHO_HIGHLIGHT "Setting up DLT Daemon." "LINE" "BLUE"
        setup_dlt
        if [[ $? != "0" ]] ; then
            return 1
        fi
    elif [[ "$setup_value" == "all" ]] ; then
        ECHO_HIGHLIGHT "Setting up GCC ARM Tools." "LINE" "BLUE"
        setup_arm_gcc "$architecture_value"
        if [[ $? != "0" ]] ; then
            return 1
        fi
        ECHO_HIGHLIGHT "Setting up Google Test." "LINE" "BLUE"
        setup_googletest
        if [[ $? != "0" ]] ; then
            return 1
        fi
        ECHO_HIGHLIGHT "Setting up DLT Daemon." "LINE" "BLUE"
        setup_dlt
        if [[ $? != "0" ]] ; then
            return 1
        fi
    fi
fi

# Build
unset Scripts
if [[ "$build_value" == "cmake" ]] ; then
    ECHO_HIGHLIGHT "Build Cmake" "LINE" "YELLOW"
    Scripts=$(find $PROG_PATH/Cmake -name "build.sh" -not -path "$PROG_PATH/build.sh")
elif [[ "$build_value" == "freertos" ]] ; then
    ECHO_HIGHLIGHT "Build FreeRTOS" "LINE" "YELLOW"
    Scripts=$(find $PROG_PATH/FreeRTOS -name "build.sh" ! -path "$PROG_PATH/build.sh" ! -path "$PROG_PATH/FreeRTOS/external/*" )
elif [[ "$build_value" == "farm" ]] ; then
    ECHO_HIGHLIGHT "Build Funny Farm Project" "LINE" "YELLOW"
    Scripts=$(find $PROG_PATH/Cpp/FarmFunnyGame -name "build.sh" -not -path "$PROG_PATH/build.sh")
elif [[ "$build_value" == "all" ]] ; then
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

# Clean up
if [[ ! -z "$clean_value" ]]
then
    ECHO_HIGHLIGHT "Clean up ignored files and submodules." "LINE" "RED"
    git clean -dfX
    git submodule deinit --all
    return 0
fi
