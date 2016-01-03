cmake_minimum_required(VERSION 3.3)
project(MultiAgentAStar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp AStar.cpp AStar.h Player.cpp Player.h)
add_executable(MultiAgentAStar ${SOURCE_FILES})