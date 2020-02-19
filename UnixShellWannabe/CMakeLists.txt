cmake_minimum_required(VERSION 3.15.3)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main main.cpp shelpers.cpp)
set(GCC_COVERAGE_COMPILE_FLAGS "-lreadline")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

project(UnixShellWannabe)

