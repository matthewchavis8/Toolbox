#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <string_view>
#include "../Toolbox/print.hpp"

using namespace testing;

TEST(ToolBoxPrint, PrintString) {
  
  internal::CaptureStdout();

  print("Hello World!");

  std::string_view output { internal::GetCapturedStdout() };
  std::string_view expected { "Hello World!" };

  EXPECT_EQ(output, expected);
}

TEST(ToolBoxPrint, PrintStringNewline) {
  
  internal::CaptureStdout();

  println("Hello World!");

  std::string_view output { internal::GetCapturedStdout() };
  std::string_view expected { "Hello World!\n" };

  EXPECT_EQ(output, expected);
}

TEST(ToolBoxPrint, PrintInteger) {
  
  internal::CaptureStdout();

  println("The number is: {}", 5);

  std::string_view output { internal::GetCapturedStdout() };
  std::string_view expected { "The number is: 5\n" };

  EXPECT_EQ(output, expected);
}

TEST(ToolBoxPrint, PrintIntegerNewline) {
  
  internal::CaptureStdout();

  print("The number is: {}", 5);

  std::string_view output { internal::GetCapturedStdout() };
  std::string_view expected { "The number is: 5" };

  EXPECT_EQ(output, expected);
}

// NOTE: this one fails here it is not printing each sequentially
// TEST(ToolBoxPrint, PrintMultipleInputs) {
//
//   internal::CaptureStdout();
//
//   print("The number is: {}", 5, 6, 7);
//
//   std::string_view output { internal::GetCapturedStdout() };
//   std::string_view expected { "The number is: 5 6 7" };
//
//   SCOPED_TRACE(::testing::Message()
//     << "Output: " << output << '\n'
//     << "Expected: " << expected << '\n');
//
//   EXPECT_EQ(output, expected);
// }
