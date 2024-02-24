cmake_minimum_required(VERSION 2.8)
project(CmakeTutorial)
add_executable(${PROJECT_NAME} main.cxx)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

