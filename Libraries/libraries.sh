#! /bin/bash

### Libraries
# Color       #define       Value       RGB
# black     COLOR_BLACK       0     0, 0, 0
# red       COLOR_RED         1     max,0,0
# green     COLOR_GREEN       2     0,max,0
# yellow    COLOR_YELLOW      3     max,max,0
# blue      COLOR_BLUE        4     0,0,max
# magenta   COLOR_MAGENTA     5     max,0,max
# cyan      COLOR_CYAN        6     0,max,max
# white     COLOR_WHITE       7     max,max,max

function ECHO_HIGHLIGHT()
{
    if [ "$2" = "LINE" ] ; then
        if [ "$3" = "RED" ] ; then
            echo -e "\e[31m"
            echo -e "******************************************************************************"
            echo -e " $1 "
            echo -e "******************************************************************************"
            echo -n -e "\e[m"
        elif [ "$3" = "GREEN" ] ; then
            echo -e "\e[32m"
            echo -e "******************************************************************************"
            echo -e " $1"
            echo -e "******************************************************************************"
            echo -n -e "\e[m"
        elif [ "$3" = "YELLOW" ] ; then
            echo -e "\e[33m"
            echo -e "******************************************************************************"
            echo -e " $1"
            echo -e "******************************************************************************"
            echo -n -e "\e[m"
        elif [ "$3" = "BLUE" ] ; then
            echo -e "\e[34m"
            echo -e "******************************************************************************"
            echo -e " $1"
            echo -e "******************************************************************************"
            echo -n -e "\e[m"
        else
            echo -e "\e[32m"
            echo -e "******************************************************************************"
            echo -e " $1"
            echo -e "******************************************************************************"
            echo -n -e "\e[m"
        fi
    else
        if [ "$2" = "RED" ]       ; then        echo -e "\e[31m$1\e[m"
        elif [ "$2" = "YELLOW" ]  ; then        echo -e "\e[33m$1\e[m"
        elif [ "$2" = "BLUE" ]    ; then        echo -e "\e[34m$1\e[m"
        elif [ "$2" = "MAGENTA" ] ; then        echo -e "\e[35m$1\e[m"
        elif [ "$2" = "CYAN" ]    ; then        echo -e "\e[36m$1\e[m"
        elif [ "$2" = "GREEN" ]   ; then        echo -e "\e[32m$1\e[m"
        else                                    echo -e "\e[37m$1\e[m"
        fi
    fi
}

function configure_cmake()
{
    ECHO_HIGHLIGHT "Run Cmake configuration..." "MAGENTA"
    $1
    local EXIT_CODE=$?
    if [ $EXIT_CODE != "0" ]
    then
        ECHO_HIGHLIGHT "Failed to configure cmake" "RED"
        exit $EXIT_CODE
    fi
}

function build_cmake()
{
    ECHO_HIGHLIGHT "Run Cmake building..." "MAGENTA"
    $1
    EXIT_CODE=$?
    if [ $EXIT_CODE != "0" ]
    then
        ECHO_HIGHLIGHT "Failed to build cmake" "RED"
        exit $EXIT_CODE
    fi
}

function script_dir()
{
    local DIR="$( cd "$( dirname "$0" )" && pwd )"
    echo "$DIR"
}

# Run the scripts
function run_a_script()
{
    ECHO_HIGHLIGHT "Execute $1" "LINE" "YELLOW"
    $1
    local EXIT_CODE=$?
    if [ $EXIT_CODE -ne 0 ]
    then
        ECHO_HIGHLIGHT "$1 exits with EXIT_CODE=$EXIT_CODE" "LINE" "RED"
        exit 1
    fi
}

# Install neccessary environment variables for freertos
function install_freertos_enviroment()
{
    if [[ -z "FREERTOS_DIR" ]]
    then
        ECHO_HIGHLIGHT "FreeRTOS source already exposed $FREERTOS_DIR" "GREEN"
    else
        export FREERTOS_DIR="$GIT_DIRECTORY/FreeRTOS/external/FreeRTOS"
        ECHO_HIGHLIGHT "FreeRTOS source path: $FREERTOS_DIR" "GREEN"
    fi

    if [[ "$PATH" == *"gcc-arm-none-eabi-10.3-2021.10"* ]]
    then
        ECHO_HIGHLIGHT "Already install gcc arm" "GREEN"
    else
        GCC=$(find ~ -name "gcc-arm-none-eabi-10.3-2021.10")
        export PATH="$PATH:$GCC"
        ECHO_HIGHLIGHT "Export gcc arm tool to path: $GCC" "GREEN"
    fi
}
