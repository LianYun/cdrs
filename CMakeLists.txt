cmake_minimum_required(VERSION 3.9)
project(cdrs VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("third_party/leveldb")

add_executable(test main.cc)
target_link_libraries(test PUBLIC leveldb)
