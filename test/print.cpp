#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string_view>
#include "../Toolbox/print.hpp"

using namespace testing;

TEST(ToolBoxPrint, BasicString) {
  
  internal::CaptureStdout();

  print("Hello World!");

  std::string_view output { internal::GetCapturedStdout() };
  std::string_view expected { "Hello World!" };

  EXPECT_EQ(output, expected);
}

TEST(ToolBoxPrint, BasicStringNewline) {
  
  internal::CaptureStdout();

  println("Hello World!");

  std::string_view output { internal::GetCapturedStdout() };
  std::string_view expected { "Hello World!\n" };

  EXPECT_EQ(output, expected);
}
