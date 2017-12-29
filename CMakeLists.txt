cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
set (CMAKE_CXX_STANDARD 11)

project(Alignment)
add_executable(Alignment
               main.cpp text.cpp text.h compare.cpp compare.h clustering.cpp clustering.h distance.cpp distance.h word.cpp word.h tests.cpp tests.h)
