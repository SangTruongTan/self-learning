# Navigate to the build directory
cd Step5_build
cmake -S ..
sudo cmake --build . --target install --config Debug
# cmake --install . --prefix "/home/codespace/Cmake"
