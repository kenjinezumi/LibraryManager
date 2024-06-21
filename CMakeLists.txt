cmake_minimum_required(VERSION 3.10)
project(LibraryManager)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

# Create the main application target
add_executable(LibraryManager
    src/main.cpp
    src/Book.cpp
    src/Logger.cpp
    src/Library.cpp
    src/User.cpp)

# Create the tests target
add_executable(LibraryManagerTests
    tests/tests.cpp
    src/Book.cpp
    src/Logger.cpp
    src/Library.cpp
    src/User.cpp)

