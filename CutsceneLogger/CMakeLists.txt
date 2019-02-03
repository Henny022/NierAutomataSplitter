project(NieRAutomataPracticeTool)
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 11)


add_executable(NieRAutomataPracticeTool main.cpp NierAutomataMemoryHandler.h MemoryHandler.h LiveSplitSettings.h)
