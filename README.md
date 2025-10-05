# Pathfinding Algorithms Library

A C++ library implementing D* Lite. The library is designed to be modular and reusable, with an abstract IGraph interface so users can plug in custom maps or graph structures. The repository includes unit tests using GoogleTest, and a companion paper thoroughly explaining the D* Lite algorithm. 

## Features

- Modular C++ D* Lite
- Tailored heap util for D* Lite
- Unit tests using GoogleTest

## Requirements

- C++17 or higher
- CMake >= 3.14
- GoogleTest (automatically fetched via CMake)

On Linux/WSL, you may need to install development packages!

## Instructions

1. Create a build directory and build:

```bash
mkdir build
cd build
cmake ..
make
```

2. Run unit tests:

```bash
./tests/unit_tests
```
