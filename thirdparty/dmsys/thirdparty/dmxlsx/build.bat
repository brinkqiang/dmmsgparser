
rem - clone code
rem git clone https://github.com/brinkqiang/dmxlsx.git
rem pushd dmxlsx
rem git submodule update --init --recursive

rmdir /S /Q build
mkdir build
pushd build
cmake -A x64 -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build . --config relwithdebinfo
popd

rem pause