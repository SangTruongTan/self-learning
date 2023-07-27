cmake_minimum_required(VERSION 3.0)
project(Version VERSION 99.22.4)

message("Project version:${PROJECT_VERSION}")

add_definitions(-D__VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
                -D__VERSION_MINOR=${PROJECT_VERSION_MINOR}
                -D__VERSION_PATCH=${PROJECT_VERSION_PATCH})

add_executable(${PROJECT_NAME}
               main.cxx
               Version.cxx)
