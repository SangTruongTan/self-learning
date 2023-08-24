cmake_minimum_required(VERSION 3.13)
project(test)
add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/library/include/")

target_link_directories(${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/library/lib/")

target_link_libraries(${PROJECT_NAME} mearlymath)
