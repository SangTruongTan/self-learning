# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.13)

# Append CMake Module paths
list(APPEND CMAKE_MODULE_PATH
     "${CMAKE_CURRENT_SOURCE_DIR}/unittests/cmake-modules")

# Include Git repo root module
include(RepoRoot)

# Set CXX Standard flag
set(CXX_STANDARD_REQUIRED 11)

# Set Optimization flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Set Debug flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Set other flags as needed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Set the project name
project(FarmFunnyGame)

# MacDonald library Set the library name as a variable
set(MACDONALD_LIB MacDonald)

# Get all source files in the src directory
file(GLOB MACDONALD_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx")

# Add your source files to the project
add_library(${MACDONALD_LIB} SHARED ${MACDONALD_LIB_SOURCES})

# Include directories
target_include_directories(
    ${MACDONALD_LIB}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/"
            "${REPO_ROOT}/external/dlt-daemon/include/"
            "${REPO_ROOT}/external/dlt-daemon/include/dlt/"
            "${REPO_ROOT}/external/dlt-daemon/build/include/"
            "${REPO_ROOT}/external/dlt-daemon/build/include/dlt/")

# Link target directories
target_link_directories(
    ${MACDONALD_LIB} PRIVATE "${REPO_ROOT}/external/dlt-daemon/build/src/lib/")

# Target link libraries
target_link_libraries(${MACDONALD_LIB} PRIVATE ncurses pthread gcov)

# Add your main executable and link with the target from src /
add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/include"
            "${REPO_ROOT}/external/dlt-daemon/include/"
            "${REPO_ROOT}/external/dlt-daemon/include/dlt/"
            "${REPO_ROOT}/external/dlt-daemon/build/include/"
            "${REPO_ROOT}/external/dlt-daemon/build/include/dlt/")

target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src"
    "${REPO_ROOT}/external/dlt-daemon/build/src/lib/")

target_link_libraries(${PROJECT_NAME} PRIVATE ${MACDONALD_LIB} dlt ncurses pthread)
