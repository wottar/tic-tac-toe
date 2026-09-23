cmake_minimum_required(VERSION 3.16)
project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3 -Wall -Wextra -pedantic)

add_library(tictactoe_lib src/TicTacToe.cpp)
target_include_directories(tictactoe_lib PUBLIC include)

add_executable(tic-tac-toe src/main.cpp)
target_link_libraries(tic-tac-toe PRIVATE tictactoe_lib)