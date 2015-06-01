cmake_minimum_required(VERSION 3.2)
project(reversi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp reversi_game.cpp)
add_executable(reversi ${SOURCE_FILES})