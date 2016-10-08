cmake_minimum_required(VERSION 3.3)

project(reversi C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# set(Qt5Widgets_DIR "/opt/qt/5.4/gcc/lib/cmake/Qt5Widgets")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set("QMAKE_MAC_SDK.macosx.version = 10.11")

find_package(QT5PrintSupport REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Sql REQUIRED)

set(RESOURCE ${CMAKE_SOURCE_DIR}/images/images.qrc ${CMAKE_SOURCE_DIR}/sounds/sounds.qrc ${CMAKE_SOURCE_DIR}/languages/languages.qrc)
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})

set(SOURCE_FILES
        src/main.cpp
        src/mainwindow.cpp
        src/reversi_game.cpp
        src/clickablelabel.cpp
        src/random_reversi_player.cpp
        src/highscore_dialog.cpp
        src/playername_dialog.cpp
        src/reversi_player_thread.cpp)

set(HEADER_FILES
        src/direction.h
        src/piece.h
        src/reversi_game.h
        src/square.h src/utils.h
        src/mainwindow.h
        src/clickablelabel.h
        src/random_reversi_player.h
        src/interface_reversi_player.h
        src/highscore_dialog.h
        src/playername_dialog.h
        src/reversi_player_thread.h)

add_executable(reversi ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_ADDED})

target_link_libraries(reversi Qt5::Widgets Qt5::Multimedia Qt5::Sql Qt5::PrintSupport)


# gtest stuff
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(reversi_tests test/direction_test.cpp test/reversi_test.cpp src/reversi_game.cpp)
target_link_libraries(reversi_tests /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a ${CMAKE_THREAD_LIBS_INIT})
enable_testing()
add_test(reversitest reversi_tests)

find_package(Doxygen)

if (DOXYGEN_FOUND)

    set(DOXYGEN_INPUT Doxygen)
    set(DOXYGEN_OUTPUT doc)

    add_custom_command(
        OUTPUT ${DOXYGEN_OUTPUT}
        COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
        COMMAND ${CMAKE_COMMAND} -E echo "Done."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${DOXYGEN_INPUT}
    )

    add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

    add_custom_target(apidoc_forced
        COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
        COMMAND ${CMAKE_COMMAND} -E echo "Done."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

endif (DOXYGEN_FOUND)