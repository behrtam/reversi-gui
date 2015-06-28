cmake_minimum_required(VERSION 2.8)
project(reversi C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#﻿set(Qt5Widgets_DIR "/opt/qt/5.4/gcc/lib/cmake/Qt5Widgets")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#if (CMAKE_COMPILER_IS_GNUCXX)
#  add_definitions(-Wall -Wextra
#    -fvisibility=hidden
#    -Wno-non-virtual-dtor
#    -Wno-unknown-pragmas
#    -Wno-long-long
#    -Wno-unknown-pragmas
#    -Wno-unused-function
#    -Wno-variadic-macros)


#elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
#  set(CMAKE_COMPILER_IS_CLANG true CACHE INTERNAL "Is CLang compiler (clang++)")
  # add clang specific warning levels
#  add_definitions(-Weverything)
  # .. and disable some of the harmless ones
  #add_definitions(
                  #-Wno-sign-conversion
                  # These are warnings of low severity, which are disabled
                  # for now until we are down to a reasonable size of warnings.
                  #-Wno-long-long
                  #-Wno-padded
                  #-Wno-global-constructors
                  #-Wno-exit-time-destructors
                  #-Wno-weak-vtables
                  #-Wno-documentation-unknown-command
                  #-Wno-undef
                  #-Wno-documentation
                  #-Wno-source-uses-openmp
                  # These are warnings of moderate severity, which are disabled
                  # for now until we are down to a reasonable size of warnings.
                  #-Wno-conversion
                  #-Wno-float-equal
                  #-Wno-switch-enum
                  #-Wno-missing-prototypes
                  #-Wno-missing-variable-declarations
                  #)
#endif()

## -Wconversion flag for gcc
#set(CXX_WARN_CONVERSION OFF CACHE BOOL "Enables warnings for type conversion problems (GCC only)")
#if (CXX_WARN_CONVERSION)
#	if (CMAKE_COMPILER_IS_GNUCXX)
#		add_definitions(-Wconversion)
#	endif()
#endif()

find_package(Qt5Widgets)
find_package(Qt5Multimedia)

set(RESOURCE ${CMAKE_SOURCE_DIR}/images/images.qrc ${CMAKE_SOURCE_DIR}/sounds/sounds.qrc)
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})

set(SOURCE_FILES src/main.cpp src/mainwindow.cpp src/reversi_game.cpp src/clickablelabel.cpp src/random_reversi_player.cpp)
set(HEADER_FILES src/direction.h src/piece.h src/reversi_game.h src/square.h src/utils.h src/mainwindow.h src/clickablelabel.h src/random_reversi_player.h src/interface_reversi_player.h)
add_executable(reversi ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_ADDED})
target_link_libraries(reversi Qt5::Widgets Qt5::Multimedia)

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