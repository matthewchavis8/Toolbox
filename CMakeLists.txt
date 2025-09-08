cmake_minimum_required(VERSION 3.21)
project(Toolbox LANGUAGES CXX)

# Set standard if not set already
if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Demo Executable
add_executable(
  demo_with_toolbox
  main.cpp
)

#  -- Enable Google Test --
include(CTest)

if(BUILD_TESTING)
  # For MSVC compilers avoid conflict
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  FetchContent_MakeAvailable(googletest)

  add_subdirectory(test)
endif()
