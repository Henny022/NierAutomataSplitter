cmake_minimum_required(VERSION 2.8)

project(CutsceneLogger)

file(GLOB headerFiles ../include/*.h)
file(GLOB sourceFiles ../src/*.cpp)

add_executable(CutsceneLogger ${headerFiles} ${sourceFiles})

target_include_directories(CutsceneLogger PUBLIC ../include)

source_group("Header Files" FILES ${headerFiles})
source_group("Source Files" FILES ${sourceFiles})