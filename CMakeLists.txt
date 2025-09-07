cmake_minimum_required(VERSION 3.21)
project(Toolbox LANGUAGES CXX)

# Set standard if not set already
if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO: add Google Test eventually
# add_subdirectory(test)

# Test Executable
add_executable(
  demo
  main.cpp
)
