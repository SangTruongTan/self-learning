# Include Colorize Message module
include(${CMAKE_CURRENT_LIST_DIR}/ColorizeMessage.cmake)

# # Replace spaces with semicolons
separate_arguments(TARGET_BIN)

# Show Information
message("🍗🍗🍗 ${Yellow}TARGET_PATH=${TARGET_PATH}${ColourReset}")
message("🍠🍠🍠 ${Yellow}TARGET_BIN=${TARGET_BIN}${ColourReset}")



# run test scripts
foreach(BIN ${TARGET_BIN})
    message("Run 🚀🚁💺: ${TARGET_PATH}/${BIN} --gtest_output=xml:reports/${BIN}-result.xml")
    execute_process(COMMAND ${TARGET_PATH}/${BIN} --gtest_output=xml:reports/${BIN}-result.xml)
endforeach()
