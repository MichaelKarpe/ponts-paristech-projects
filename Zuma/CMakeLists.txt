cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(Zuma)
add_executable(Zuma
               zuma.cpp serpent.cpp serpent.h bille.cpp bille.h grenouille.cpp grenouille.h trajectoire.cpp trajectoire.h outils.cpp outils.h niveau.cpp niveau.h)
ImagineUseModules(Zuma Graphics)
