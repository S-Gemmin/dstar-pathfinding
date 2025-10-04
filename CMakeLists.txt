cmake_minimum_required(VERSION 3.14)
project(PathfindingAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library target
add_library(pathfinding
    src/AStar.cpp
    src/DStarLite.cpp
    src/Grid.cpp
    src/MinHeapMap.cpp
)

target_include_directories(pathfinding PUBLIC include)

# === Unit Tests ===
enable_testing()
add_subdirectory(tests)
