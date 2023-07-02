# Navigate to build directory
cd Step6_build
cmake -S ..
ctest [-VV] -C Debug -D Experimental
