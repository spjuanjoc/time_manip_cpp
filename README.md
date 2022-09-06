# Time manipulation

Time manipulation with chrono and fmt.  
Get system time and print it:

## Build

    cmake -DCMAKE_MODULE_PATH=$PWD -DCMAKE_BUILD_TYPE=Debug -G "Ninja" ..
    cmake --build ./ -- -j6                                                           

## Run

    ./time_manip_cpp

## Requirements

- A compiler version that supports c++20 (gcc-9)
- Conan > 1.51.1
