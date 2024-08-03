cmake_minimum_required(VERSION 3.28)
project(ESLM-CPP)

set(CMAKE_CXX_STANDARD 20)

# Ensure these paths are correct for your MinGW installation
set(CMAKE_C_COMPILER "E:/msys/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "E:/msys/mingw64/bin/g++.exe")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    "${CMAKE_SOURCE_DIR}/include"
    "E:/msys/mingw64/include"
    "E:/msys/mingw64/include/c++/14.1.0"
)

link_directories(
    "E:/msys/mingw64/lib"
)

# Armadillo Paths
set(ARMADILLO_INCLUDE_DIR "E:/msys/mingw64/include")
set(ARMADILLO_LIBRARY "E:/msys/mingw64/lib/libarmadillo.dll.a")

find_package(Armadillo REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})

# Ensure Armadillo include directory and lib path
target_include_directories(main PRIVATE 
    "${CMAKE_SOURCE_DIR}/include" 
    "E:/msys/mingw64/include" 
    "E:/msys/mingw64/include/c++/14.1.0"
    ${ARMADILLO_INCLUDE_DIR}
)

target_link_libraries(main PRIVATE igraph pthread ${ARMADILLO_LIBRARY})
