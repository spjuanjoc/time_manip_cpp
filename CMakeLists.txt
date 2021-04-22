cmake_minimum_required(VERSION 3.17)
project(time_manip_cpp)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(PROJECT_OPTIONS
    -O3
    -Wpedantic
    -Wall
    -Wextra
    -Werror
    )
target_compile_options(${PROJECT_NAME} INTERFACE ${PROJECT_OPTIONS})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
conan_target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})
message("${CONAN_LIBS}")
