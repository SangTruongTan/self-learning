cmake_minimum_required(VERSION 3.13)
project(ep5)

option(USE_ADDER "A simple library for adding 2 floats." ON)
if (USE_ADDER)
    add_subdirectory(AdderLib)

    list(APPEND EXTRA_LIBS_DIRS "${PROJECT_BINARY_DIR}/AdderLib")
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/AdderLib")
    list(APPEND EXTRA_LIBS "mearlymath")

endif()

configure_file(ep5Config.h.in ep5Config.h)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_BINARY_DIR}
    ${EXTRA_INCLUDES})

target_link_directories(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS_DIRS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS})
