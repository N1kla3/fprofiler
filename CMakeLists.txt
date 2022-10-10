cmake_minimum_required(VERSION 3.22)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(json)


add_executable(untitled main.cpp Core.cpp Core.h StompProfiler.cpp StompProfiler.h)

target_link_libraries(untitled nlohmann_json::nlohmann_json)
