# Pathfinding Algorithms Library

A C++ library implementing and benchmarking multiple pathfinding algorithms, including A*, and D* Lite. The library is designed to be modular and reusable, with an abstract IGraph interface so users can plug in custom maps or graph structures. The repository also includes unit tests using GoogleTest. A companion paper thoroughly explains the D* Lite algorithm. 

## Features

- Modular C++ library for pathfinding algorithms
- Tailored heap util for D* Lite
- Unit tests using GoogleTest

## Requirements

- C++17 or higher
- CMake >= 3.14
- GoogleTest (automatically fetched via CMake)

On Linux/WSL, you may need to install development packages!

## Build Instructions

1. Clone the repository:

```bash
git clone <repo-url>
cd pathfinding-algos
```

2. Create a build directory and run CMake:

```bash
mkdir build
cd build
cmake ..
```

3. Build all targets:

```bash
make -j
```

4. Run unit tests:

```bash
ctest
./tests/unit_tests
```

## Benchmarking

Benchmarks are located in `benchmarks/`.

Executables produce CSV results, which can be plotted in MATLAB:

```bash
./pathfinding_benchmark
```

MATLAB script example: `scripts/matlab/benchmark_plot.m`
