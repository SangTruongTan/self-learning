Requires for dependencies
libglew-dev

Submodule adding
git submodule add <submodule_path>

Normal Build and Install to /usr/local
cmake -S . -B ./out/build
cmake --build ./out/build --target install

Build and Install to custom directory
cmake -S . -B ./out/build -DCMAKE_INSTALL_PREFIX=./library
cmake --build ./out/build --target install

Build and Generate CPack package
cmake -S . -B ./out/build
cmake --build ./out/build --target package
