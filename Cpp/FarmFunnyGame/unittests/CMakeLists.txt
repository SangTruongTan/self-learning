# CMake minimum required
cmake_minimum_required(VERSION 3.21.7)

# Project Name
project(FunnyFarmTest)

# Append CMake Module paths
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

# Include Colorize module
include(ColorizeMessage)

# Set CXX Standard flag
set(CXX_STANDARD_REQUIRED 11)

# Set Optimization flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Set Debug flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Set other flags as needed
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra -fprofile-arcs -ftest-coverage")

# Number of Processing Core
include(ProcessorCount)
ProcessorCount(PROCESSOR_COUNT)
message("${Green}### Procesor count: ${PROCESSOR_COUNT} ###${ColourReset}")

# Download all the submodules.
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../.git")
    # Update submodules as needed.
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodules update.")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(
                FATAL_ERROR
                    "git submodule update --init failed with ${GIT_SUBMOD_RESULT}. please checkout submodules."
            )
        endif()
    endif()
endif()

# MacDonald library Set the library name as a variable
set(MACDONALD_LIB MacDonald)

# Get all source files in the src directory
file(GLOB MACDONALD_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cxx")

# Add your source files to the project
add_library(
    ${MACDONALD_LIB} SHARED
    ${MACDONALD_LIB_SOURCES})

# Include directories
target_include_directories(${MACDONALD_LIB}
                           PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# Target link libraries
target_link_libraries(${MACDONALD_LIB} PRIVATE ncurses pthread gcov)

# Chicken Coverage
set(CHICKEN Chicken)

# Add your project's source files
add_executable(
    ${CHICKEN} "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/gtest_main.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/UT_GMOCK_Chicken.cpp")

# Add your project's include directories
target_include_directories(
    ${CHICKEN}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../external/googletest/googletest/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/fake/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../src/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# Link target directories
target_link_directories(
    ${CHICKEN} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../external/googletest/build/lib")

# Link target libraries
target_link_libraries(${CHICKEN} PRIVATE gtest gcov ncurses pthread
                                         ${MACDONALD_LIB})

# User Interface coverage
set(USER_INTERFACE UserInterface)

# Add your project's source files
add_executable(
    ${USER_INTERFACE} "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/gtest_main.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/UT_GMOCK_UserInterface.cpp")

# Add your project's include directories
target_include_directories(
    ${USER_INTERFACE}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../external/googletest/googletest/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/fake/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../src/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# Link target directories
target_link_directories(
    ${USER_INTERFACE} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../external/googletest/build/lib")

# Link target libraries
target_link_libraries(${USER_INTERFACE} PRIVATE gtest gcov ncurses pthread
                                         ${MACDONALD_LIB})

# Code Coverage Set Target list
SET(ALL_TARGET ${CHICKEN} ${USER_INTERFACE}
)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    append_coverage_compiler_flags()

    set(LCOV_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lcovrc")

    message("${Yellow}\nSetup for ${CHICKEN} target 🍕🍕🍕${ColourReset}")
    setup_target_for_coverage_lcov(
        NAME
        ${CHICKEN}_coverage_lcov
        EXECUTABLE
        ${CHICKEN}
        DEPENDENCIES
        ${CHICKEN}
        LCOV_ARGS
        "--config-file;${LCOV_CONF_PATH}"
        EXCLUDE
        "/usr/include/*"
        "/*/*.h"
        "/*/unittests/testscripts/*"
        BASE_DIRECTORY
        "${CMAKE_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/${CHICKEN}.dir"
        GENHTML_ARGS
        "--branch-coverage")

        message("${Yellow}\nSetup for ${USER_INTERFACE} target 🌭🌭🌭${ColourReset}")
        setup_target_for_coverage_lcov(
            NAME
            ${USER_INTERFACE}_coverage_lcov
            EXECUTABLE
            ${USER_INTERFACE}
            DEPENDENCIES
            ${USER_INTERFACE}
            LCOV_ARGS
            "--config-file;${LCOV_CONF_PATH}"
            EXCLUDE
            "/usr/include/*"
            "/*/*.h"
            "/*/unittests/testscripts/*"
            BASE_DIRECTORY
            "${CMAKE_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/${USER_INTERFACE}.dir"
            GENHTML_ARGS
            "--branch-coverage")

    message("${Yellow}\nSetup for ${ALL_TARGET} 🍔🍔🍔${ColourReset}")
    setup_target_for_coverage_lcov(
        NAME
        all_coverage_lcov
        EXECUTABLE
        ${ALL_TARGET}
        DEPENDENCIES
        ${ALL_TARGET}
        LCOV_ARGS
        "--config-file;${LCOV_CONF_PATH}"
        EXCLUDE
        "/usr/include/*"
        "/*/*.h"
        "/*/unittests/testscripts/*"
        BASE_DIRECTORY
        "${CMAKE_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}"
        GENHTML_ARGS
        "--branch-coverage")
endif()
