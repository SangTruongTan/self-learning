# Require libraries and dependencies
## Build environment
`sudo apt install build-essential`
## Extra libraries
### Curse library
`sudo apt install libncurses5-dev`
### DLT-Daemon
`sudo apt-get install cmake zlib1g-dev libdbus-glib-1-dev build-essential binutils`

# Navigate to your developement directory
```bash
git clone https://github.com/GENIVI/dlt-daemon.git
cd ./dlt-daemon

# Create build directory
mkdir build
cd ./build

# Build
cmake ..
make

# Install dlt-daemon binaries
sudo make install
sudo ldconfig
```