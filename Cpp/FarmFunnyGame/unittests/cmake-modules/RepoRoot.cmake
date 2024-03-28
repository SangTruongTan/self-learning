execute_process(COMMAND git rev-parse --show-cdup
  WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
  OUTPUT_VARIABLE relative_path_to_repository_root)

get_filename_component(REPO_ROOT
  "${CMAKE_CURRENT_LIST_DIR}/${relative_path_to_repository_root}"
  ABSOLUTE)

# Dipose of the new line
string(REPLACE "\n" "" REPO_ROOT ${REPO_ROOT})
# Replace the last "/" with an empty string
string(REGEX REPLACE "\/$" "" REPO_ROOT "${REPO_ROOT}")

message(STATUS "REPO_ROOT=${REPO_ROOT}")
