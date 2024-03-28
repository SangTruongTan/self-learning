cmake_minimum_required(VERSION 3.21.7)

# Options
option(GIT_UPDATE "Require to update the git submodules" OFF)

project(EP9 VERSION 3.2.3)
# cmake_policy(SET CMP0072 OLD)

# Find package
find_package(GLEW REQUIRED)
message("GLEW version: ${GLEW_VERSION}")
message("GLEW Include Directory: ${GLEW_INCLUDE_DIRS}")
message("GLEW Libraries: ${GLEW_LIBRARIES}")

find_package(OpenGL REQUIRED)
message("OpenGL Include Directory: ${OPENGL_INCLUDE_DIR}")
message("OpenGL OPENGL Libraries: ${OPENGL_opengl_LIBRARY}")
message("OpenGL GLU Libraries: ${OPENGL_glu_LIBRARY}")
message("OPENGL GL platform: ${OpenGL_GL_PREFERENCE}")
# If the CMP0072 is not set to "OLD". This path will be empty, uses opengl lib instead.
message("OpenGL GL Libraries: ${OPENGL_gl_LIBRARY}")

find_package(GLUT REQUIRED)
message("GLUT Include Directory: ${GLUT_INCLUDE_DIR}")
message("GLUT Libraries: ${GLUT_LIBRARIES}")

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

configure_file(ep9Config.h.in ep9Config.h)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/src
    ${PROJECT_BINARY_DIR}
    ${EXTRA_INCLUDES}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR})

target_link_directories(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS_DIRS}
    external/glfw/src
    ${GLEW_LIBRARIES}
    #{OPENGL_opengl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLUT_LIBRARIES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${EXTRA_LIBS}
    glfw
    GLEW
    OpenGL
    GLU
    glut)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/ep9Config.h" DESTINATION include)

# CPack installation
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")
include(CPack)
