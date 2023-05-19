# Navigate to the build directory
cd Step2_build
cmake -S .. -DUSE_MYMATH=OFF
# cmake -DUSE_MYMATH=ON -S ..
cmake --build .
