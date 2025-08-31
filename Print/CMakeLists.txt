add_library(
  print
  STATIC
  print.cpp
)

target_include_directories(
  print
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
