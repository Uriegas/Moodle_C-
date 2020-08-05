#Simple CMakeLists.txt, it is just a template
cmake_minimum_required(VERSION 3.2)

project(moodle)

#if want to include libraries decomment this
#include_dir()
#add_library()

##Debuging Symbols and Optimization Activated
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(include)
##Uncomment for Realese Mode and Comment above macro
##set(CMAKE_BUILD_TYPE Release)

#building project
add_executable(moodle src/main.cpp)
target_link_libraries(moodle PRIVATE moodle_lib)