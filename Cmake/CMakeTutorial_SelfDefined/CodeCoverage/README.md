Requires for dependencies
lcov clang-format gcovr

Submodule adding
git submodule add <submodule_path>

Build and Generate Code Coverage
cmake -DCMAKE_BUID_TYPE=Debug -S $DIR -B $DIR/out/build
cmake --build $DIR/out/build --target CodeCoverage_coverage_gcovr CodeCoverage_coverage_lcov
