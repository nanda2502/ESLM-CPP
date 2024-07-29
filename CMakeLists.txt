cmake_minimum_required(VERSION 3.28)
project(ESLM-CPP)
set(CMAKE_CXX_STANDARD 20)
include_directories("C:/Program Files (x86)/igraph/include/igraph" "E:/include/armadillo" "C:/OpenBLAS/include")
link_directories("C:/Program Files (x86)/igraph/lib" "C:/Program Files/OpenBLAS/lib")

add_executable(main main.cpp)
target_link_libraries(main igraph openblas pthread)