#!/bin/bash

OUTPUT_DIR="out"
SRC_DIR=".."
JAVA_MAIN_FILE="Demo.java"

declare -i CompileFailed=0
declare -i RunFailed=0

function java_compile() {
    echo "Compiling... $1"
    javac -d ${OUTPUT_DIR} -sourcepath ${SRC_DIR} $1
    if [[ $? -ne 0 ]]; then
        CompileFailed=$((CompileFailed + 1))
    fi
}

function java_run() {
    echo "Running... $1"
    java -cp "${OUTPUT_DIR}" $1
    if [[ $? -ne 0 ]]; then
        RunFailed=$((RunFailed + 1))
    fi
}

function java_build_and_run() {
    # Run each main file
    for main_file in $(find "${SRC_DIR}" -name "${JAVA_MAIN_FILE}"); do
        echo "Main file:${main_file}"
        # Compile
        java_compile ${main_file}

        # Get the path and file name
        class_path="${main_file%.*}" # Remove the extension
        main_class=$(echo "${class_path}" | sed "s|${SRC_DIR}/||;s|/|.|g") # Covert path to package name
        java_run ${main_class}
        echo ""
        echo "******************"
        echo ""
    done
}

java_build_and_run
echo "CompileFailed: ${CompileFailed}"
echo "RunFailed: ${RunFailed}"
if [[ ${CompileFailed} -ne 0 ]] || [[ ${RunFailed} -ne 0 ]]; then
    exit 1
fi
