# CMake minimum required
cmake_minimum_required(VERSION 3.21.7)

# Project Name
project(FunnyFarmTest)

# Coloring the message
if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold "${Esc}[1m")
    set(Red "${Esc}[31m")
    set(Green "${Esc}[32m")
    set(Yellow "${Esc}[33m")
    set(Blue "${Esc}[34m")
    set(Magenta "${Esc}[35m")
    set(Cyan "${Esc}[36m")
    set(White "${Esc}[37m")
    set(BoldRed "${Esc}[1;31m")
    set(BoldGreen "${Esc}[1;32m")
    set(BoldYellow "${Esc}[1;33m")
    set(BoldBlue "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan "${Esc}[1;36m")
    set(BoldWhite "${Esc}[1;37m")
endif()

# Set CXX Standard flag
set(CXX_STANDARD_REQUIRED 11)

# Set Optimization flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Set Debug flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Set other flags as needed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

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
add_library(${MACDONALD_LIB} SHARED ${MACDONALD_LIB_SOURCES})

# Include directories
target_include_directories(${MACDONALD_LIB}
                           PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

# Chicken Coverage
set(CHICKEN chicken_test)

# Add your project's source files
add_executable(
    ${CHICKEN} "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/gtest_main.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/testscripts/UT_GMOCK_CHICKEN.cpp")

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
target_link_libraries(${CHICKEN} PRIVATE gtest ncurses pthread ${MACDONALD_LIB})

# Code Coverage
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/cmake-modules)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    #set(COVERAGE_EXCLUDES '*/usr/*' '*unittests*/testscripts*' '*.h*')
    # set(COVERAGE_LCOV_EXCLUDES '*/usr/*' '*unittests*/testscripts*' '*.h*') # this is optional if you want to exclude some directory from the report
    set(LCOV_EXCLUDES "/usr/include/*" "*.h")
    setup_target_for_coverage_lcov(NAME ${CHICKEN}_coverage_lcov
                                   EXECUTABLE ${CHICKEN} -j ${PROCESSOR_COUNT}
                                   DEPENDENCIES ${CHICKEN})

    setup_target_for_coverage_gcovr_html(NAME ${CHICKEN}_coverage_gcovr
                                         EXECUTABLE ${CHICKEN} -j ${PROCESSOR_COUNT}
                                         DEPENDENCIES ${CHICKEN})
endif()
