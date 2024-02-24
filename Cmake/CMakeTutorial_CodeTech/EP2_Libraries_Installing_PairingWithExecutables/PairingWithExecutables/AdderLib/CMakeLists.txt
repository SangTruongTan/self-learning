cmake_minimum_required(VERSION 3.13)
project(mearlymath)
add_library(${PROJECT_NAME} adder.cxx)

# The following line will also include the header file to the target and copy
# along with the library files.
# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER adder.h)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES adder.h DESTINATION include)
