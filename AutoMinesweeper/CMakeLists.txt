cmake_minimum_required(VERSION 3.5)

project(Aufgabe_21_AutoMinesweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Aufgabe_21_AutoMinesweeper main.cpp menu.h menu.cpp minesweeper.h minesweeper.cpp minesweeperfield.h minesweeperfield.cpp minesweeperautoplay.h minesweeperautoplay.cpp)

install(TARGETS Aufgabe_21_AutoMinesweeper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
