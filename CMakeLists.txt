cmake_minimum_required(VERSION 3.2)
project(reversi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp src/reversi_game.cpp)
add_executable(reversi ${SOURCE_FILES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(reversi_tests test/direction_test.cpp)
target_link_libraries(reversi_tests ${GTEST_BOTH_LIBRARIES})

enable_testing()
add_test(reversi_tests reversi_tests)
# make test