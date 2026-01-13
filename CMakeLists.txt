# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Battleship)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable target and source files
add_executable(Battleship
    main.cpp
    Game.cpp
    Board.cpp
    ArgParser.cpp
)

# Find Threads library (needed for multithreading if used)
find_package(Threads REQUIRED)

# Link Threads library to the executable
target_link_libraries(Battleship PRIVATE Threads::Threads)

# Optional: set output directories for binaries
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
