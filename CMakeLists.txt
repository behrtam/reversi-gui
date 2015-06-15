cmake_minimum_required(VERSION 3.2)
project(reversi)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Qt5Widgets)

set(RESOURCE ${CMAKE_SOURCE_DIR}/images/images.qrc)
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})

set(SOURCE_FILES src/main.cpp src/mainwindow.cpp src/reversi_game.cpp src/clickablelabel.cpp)
set(HEADER_FILES src/direction.h src/piece.h src/reversi_game.h src/square.h src/utils.h src/mainwindow.h src/clickablelabel.h)
add_executable(reversi ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_ADDED})
target_link_libraries(reversi Qt5::Widgets)

# gtest stuff
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(reversi_tests test/direction_test.cpp test/reversi_test.cpp src/reversi_game.cpp)
target_link_libraries(reversi_tests gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
enable_testing()
add_test(reversitest reversi_tests)


# linting stuff
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