cmake_minimum_required(VERSION 3.10)
project(string_processing_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_subdirectory(submodules/googletest)
add_subdirectory(test)
