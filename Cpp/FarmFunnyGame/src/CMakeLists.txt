# Set the library name as a variable
set(LIB_NAME MacDonald)

# Get all source files in the src directory
file(GLOB SOURCES "*.cxx")

# Add your source files to the project
add_library(${LIB_NAME} ${SOURCES})

# Include directories
target_include_directories(${LIB_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/include")
