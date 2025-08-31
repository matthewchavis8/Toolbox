cmake_minimum_required(VERSION 3.21)
project(Logger LANGUAGES CXX)

# Set standard if not set already
if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

# Add Static Libraries
add_subdirectory(Log)
add_subdirectory(Print)
# TODO: add Google Test eventually
# add_subdirectory(test)


# Test Executable
add_executable(
  test
  main.cpp
)

# Link against static libs
target_link_libraries(
  test
  PRIVATE
  log
  print
)
