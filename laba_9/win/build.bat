rmdir /s /q build
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
cmake --build .

sleep(100)
cd build