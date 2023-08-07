cmake_minimum_required(VERSION 3.13.4)

project(ep4 VERSION 1.2.4)

configure_file(ep4Config.h.in ep4Config.h)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}/)
