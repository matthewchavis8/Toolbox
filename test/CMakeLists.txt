add_executable(unit_toolbox
  print.cpp
  logger.cpp
)

target_link_libraries(unit_toolbox
  PRIVATE
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_toolbox)
