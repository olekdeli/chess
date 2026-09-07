# 1. Initialization (What you are missing)
cmake_minimum_required(VERSION 3.10)
project(Engine VERSION 1.0 LANGUAGES CXX)

# 2. C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Automatically find ALL .cpp files in the src/ directory
file(GLOB _SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# 4. Isolate main.cpp from the rest of the engine files
list(REMOVE_ITEM _SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# 5. Build the main Engine executable
add_executable(run src/main.cpp ${_SOURCES})

# 6. Compiler Optimizations
target_compile_options(run PRIVATE -O3 -march=native -flto)

# 7. Enable and link the Test Suite
enable_testing()
add_subdirectory(tests)
