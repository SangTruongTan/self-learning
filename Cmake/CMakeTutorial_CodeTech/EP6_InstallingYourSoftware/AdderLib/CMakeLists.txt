cmake_minimum_required(VERSION 3.13)

project(mearlymath)

add_library(${PROJECT_NAME} adder.cxx adder.h)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES adder.h DESTINATION include)
