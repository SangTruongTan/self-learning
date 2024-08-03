#!/bin/bash

# Set the source and output files
LIB_SRC="mathlib.cc"
LIB_NAME="libmathlib.so"
MAIN_SRC="main.cc"
MAIN_OUT="main.o"

# Compilation options
CXXFLAGS="-fPIC"
LDFLAGS="-L. -lmathlib"

# Compile the shared library
echo "Compiling shared library..."
g++ $CXXFLAGS -shared -o $LIB_NAME $LIB_SRC

# Check if the library was created successfully
if [ $? -ne 0 ]; then
    echo "Failed to compile the shared library."
    exit 1
fi

# Compile the main application
echo "Compiling main application..."
g++ -o $MAIN_OUT $MAIN_SRC $LDFLAGS

# Check if the main application was created successfully
if [ $? -ne 0 ]; then
    echo "Failed to compile the main application."
    exit 1
fi

# Run the main application
echo "Running main application..."
./$MAIN_OUT

# Check if the application ran successfully
if [ $? -ne 0 ]; then
    echo "The main application failed to run."
    exit 1
fi
