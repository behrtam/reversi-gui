cmake_minimum_required(VERSION 3.2)
project(reversi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(SOURCE_FILES src/main.cpp src/reversi_game.cpp)
set(HEADER_FILES src/direction.h src/piece.h src/reversi_game.h src/square.h src/utils.h)
add_executable(reversi ${SOURCE_FILES} ${HEADER_FILES})


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(reversi_tests test/direction_test.cpp test/reversi_test.cpp src/reversi_game.cpp)
target_link_libraries(reversi_tests gtest gtest_main)
enable_testing()
add_test(reversitest reversi_tests)


find_package(PythonInterp)
set(STYLE_FILTER -build/header_guard)
set(SOURCES_LIST ${SOURCE_FILES} ${HEADER_FILES})

if(PYTHONINTERP_FOUND)
  list(REMOVE_DUPLICATES SOURCES_LIST)
  list(SORT SOURCES_LIST)

  add_custom_target(lint
    COMMAND "${CMAKE_COMMAND}" -E chdir
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "${PYTHON_EXECUTABLE}"
            "${CMAKE_SOURCE_DIR}/tools/cpplint.py"
            "--filter=${STYLE_FILTER}"
            "--counting=detailed"
            "--extensions=cpp,hpp,h"
            "--linelength=100"
            ${SOURCES_LIST}
    DEPENDS ${SOURCES_LIST}
    COMMENT "stylecheck cpplint.py"
    VERBATIM)
    return()
endif()