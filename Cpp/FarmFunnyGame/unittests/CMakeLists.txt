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

# Chicken Coverage
set(CHICKEN chicken_test)

# Add your project's source files
add_executable(
    ${CHICKEN} ${CMAKE_CURRENT_SOURCE_DIR}/testscripts/gtest_main.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/testscripts/UT_GMOCK_CHICKEN.cpp)

# Add your project's include directories
target_include_directories(
    ${CHICKEN}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/googletest/googletest/include
)

# Link target directories
target_link_directories(
    ${CHICKEN} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/googletest/build/lib)

# Link target libraries
target_link_libraries(${CHICKEN} PRIVATE gtest)
