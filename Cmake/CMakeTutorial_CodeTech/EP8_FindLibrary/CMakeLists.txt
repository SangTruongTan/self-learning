cmake_minimum_required(VERSION 3.21.7)

# Options
option(GIT_UPDATE "Require to update the git submodules" OFF)

project(EP8 VERSION 3.2.3)

# FIND LIBRARY FOR CMAKE 3.21.7 [REQUIRED] IS AVAILABLE.
find_library(myglewlib glew NAMES glew2 GLEW GLEW2 DOC "glew library")
if(${myglewlib} STREQUAL myglewlib-NOTFOUND)
    message(FATAL_ERROR "no glew, sad day")
else()
    message(STATUS "glew found! as ${myglewlib}")
endif()

find_library(myglulib glu NAMES GLU DOC "glu library")
if(${myglulib} STREQUAL myglulib-NOTFOUND)
    message(FATAL_ERROR "no glu, sad day")
else()
    message(STATUS "glu found! as ${myglulib}")
endif()

# [REQUIRED] is involved.
find_library(mygllib gl NAMES GL DOC "gl library" REQUIRED)
if(${myglulib} STREQUAL myglulib-NOTFOUND)
    message(FATAL_ERROR "no gl, sad day")
else()
    message(STATUS "gl found! as ${mygllib}")
endif()

# Download all the submodules.
if(GIT_UPDATE)
    message("Updating submodules 💻💻💻")
    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/../../../.git")
    # Update submodules as needed.
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
            message(STATUS "Submodules update.")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}. please checkout submodules.")
            endif()
        endif()
    endif()
endif()

# Check all the submodules.
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(external/glfw)

option(USE_ADDER "A simple library for adding 2 floats." ON)
if (USE_ADDER)
    add_subdirectory(AdderLib)

    list(APPEND EXTRA_LIBS_DIRS "${PROJECT_BINARY_DIR}/AdderLib")
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/AdderLib")
    list(APPEND EXTRA_LIBS "mearlymath")

endif()

configure_file(ep8Config.h.in ep8Config.h)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/src
    ${PROJECT_BINARY_DIR}
    ${EXTRA_INCLUDES})

target_link_directories(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS_DIRS}
    external/glfw/src)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS}
    glfw
    ${myglewlib}
    ${myglulib}
    ${mygllib})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/ep8Config.h" DESTINATION include)

# CPack installation
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")
include(CPack)
