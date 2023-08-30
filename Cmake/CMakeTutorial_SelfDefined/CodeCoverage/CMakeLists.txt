cmake_minimum_required(VERSION 3.21.7)

project(CodeCoverage VERSION 1.0.0)

add_executable(${PROJECT_NAME} main.cxx)
include(ProcessorCount)
ProcessorCount(PROCESSOR_COUNT)
message("### Procesor count: ${PROCESSOR_COUNT}")

# Download all the submodules.
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


LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/external/cmake-modules)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    # set(COVERAGE_LCOV_EXCLUDES 'dir1/*' 'dir2/*') // this is optional if you want to exclude some directory from the report
    setup_target_for_coverage_lcov(NAME ${PROJECT_NAME}_coverage_lcov
                                   EXECUTABLE ${PROJECT_NAME} -j ${PROCESSOR_COUNT}
                                   DEPENDENCIES ${PROJECT_NAME})

    setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_coverage_gcovr
                                         EXECUTABLE ${PROJECT_NAME} -j ${PROCESSOR_COUNT}
                                         DEPENDENCIES ${PROJECT_NAME})
endif()
