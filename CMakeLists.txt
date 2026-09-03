# 1. Initialization
cmake_minimum_required(VERSION 3.10)
project(ChessEngine VERSION 1.0 LANGUAGES CXX)

# 2. C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. The Target (Executable)
add_executable(run 
    main.cpp
    src/game.cpp
)

# 4. Compiler Optimizations
#target_compile_options(main PRIVATE -O3 -march=native -flto)
