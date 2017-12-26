cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)

project(Alignment)
add_executable(Alignment
               main.cpp text.cpp text.h)
