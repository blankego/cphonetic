cmake_minimum_required(VERSION 2.8)
project(cphonetic)
list(APPEND CMAKE_CXX_FLAGS -std=c++11)
INCLUDE_DIRECTORIES(include mandarin) 

add_subdirectory(mandarin)
add_subdirectory(include)
add_subdirectory(test)
add_subdirectory(playground)
