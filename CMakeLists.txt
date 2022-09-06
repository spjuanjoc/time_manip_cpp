cmake_minimum_required(VERSION 3.17)

project(time_manip_cpp
  VERSION "0.0.2"
  DESCRIPTION "time manipulation"
  LANGUAGES CXX
)

add_executable(${PROJECT_NAME} main.cpp)


## Options
set(PROJECT_OPTIONS
  -O3
  -Wpedantic
  -Wall
  -Wextra
  -Werror
)


## Setup Conan
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    )
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_autodetect(settings)
conan_check(REQUIRED)
conan_cmake_run(CONANFILE conanfile.txt
  BASIC_SETUP NO_OUTPUT_DIRS
  BUILD missing
  SETTINGS ${settings}
)


## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(fmt    REQUIRED)


## Target
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_compile_options(${PROJECT_NAME} INTERFACE ${PROJECT_OPTIONS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
