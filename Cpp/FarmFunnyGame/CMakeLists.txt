# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.13)

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

# Add the source directory
add_subdirectory(src)

# Add your main executable and link with the target from src/
add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME}
                           PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PRIVATE MacDonald dlt ncurses pthread)
