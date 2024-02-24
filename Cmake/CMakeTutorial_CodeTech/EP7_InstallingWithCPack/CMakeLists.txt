cmake_minimum_required(VERSION 3.13)
project(EP7 VERSION 3.2.3)

option(USE_ADDER "A simple library for adding 2 floats." ON)
if (USE_ADDER)
    add_subdirectory(AdderLib)

    list(APPEND EXTRA_LIBS_DIRS "${PROJECT_BINARY_DIR}/AdderLib")
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/AdderLib")
    list(APPEND EXTRA_LIBS "mearlymath")

endif()

configure_file(ep7Config.h.in ep7Config.h)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_BINARY_DIR}
    ${EXTRA_INCLUDES})

target_link_directories(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS_DIRS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/ep7Config.h" DESTINATION include)

# CPack installation
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")
include(CPack)
