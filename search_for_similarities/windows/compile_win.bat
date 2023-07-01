mkdir build
cd build
cmake ..
cmake -G "Visual Studio 17 2022" ./CMakeLists.txt
cmake --build . --config Release --target ALL_BUILD