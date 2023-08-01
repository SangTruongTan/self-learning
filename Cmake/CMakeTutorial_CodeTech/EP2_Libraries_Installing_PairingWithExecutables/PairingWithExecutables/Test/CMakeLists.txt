cmake_minimum_required(VERSION 3.13)
project(test)
add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} mearlymath)
