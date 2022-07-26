cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(GUI VERSION 0.1)

add_executable(GUI
    gui/main.cpp
    gui/SolverWindow.cpp
)

target_link_libraries(GUI PRIVATE SDL2 pthread)
