#pragma once

#include <cstddef>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <tuple>

/**
 * @file format.hpp
 * @brief Lightweight formatting utilite using vardiac templates
 *
 * Supports C++ 17 and up. Provides 'print' and 'println' for formatting output
 * similar to Pythons print or Rust println.
 */



/**
 * @brief Outputs a std::string_view safely to the provided stream.
 * 
 * This overload ensures null-terminated strings like `const char*` are
 * handled safely as string views.
 * 
 * @param os   Output stream (e.g., `std::ostringstream`, `std::cout`)
 * @param str  The string to write to the stream
 */
inline void output(std::ostream& os, std::string_view str) { os << str; }

/**
 * @brief Outputs a std::string_view safely to the provided stream.
 * 
 * This overload ensures null-terminated strings like `const char*` are
 * handled safely as string views.
 * 
 * @param os   Output stream (e.g., `std::ostringstream`, `std::cout`)
 * @param str  The string to write to the stream
 */
template <typename T>
inline void output(std::ostream& os, const T& value) { os << value; }

/**
 * @brief Prints a formatted string to `std::cout` using `{}` placeholders.
 *
 * Supports escaping with `{{` and `}}`. Throws if the number of `{}` mismatches
 * the number of provided arguments.
 *
 * @tparam Args  Variadic argument types
 * @param fmt    Format string with `{}` placeholders
 * @param args   Arguments to substitute into the format string
 *
 * @throws std::runtime_error if placeholder count doesn't match argument count
 */
template <typename... Args>
inline void print(std::string_view fmt, const Args&... args) {
  std::ostringstream oss;
  auto it { fmt.begin() };  // Iterator to current character in the fmt
  auto end { fmt.end() };   // Iterator to the end of the fmt
  std::size_t idx { 0 };    // Tracks current arg index

  // Packing variadic args into a tuple container for subscript access
  auto container { std::make_tuple(args...) };

  // Amount of arguments
  constexpr std::size_t n { sizeof...(Args) };
  
  // Format loopn
  while (it != end) {
    if (*it == '{' && std::next(it) != end && *std::next(it) == '}') {
      // Check if {} is not 0
      if (idx >= n)
        throw std::runtime_error("Too few arguments for format string");
      
      // Logic to print the correct element from the tuple when '{}' is encountered
      std::apply(
        [&](const auto&... unpacked) {
          std::size_t container_idx { 0 };
          ((container_idx == idx ? output(oss, unpacked) : void()), ...);
        }
        , container);
      
      ++idx;
      std::advance(it, 2);
    } else if (*it == '{' && std::next(it) != end && *std::next(it)== '{') {     // Handles escaped braces: '{{}}'
      oss << '{';
      std::advance(it, 2);
    } else if (*it == '}' && std::next(it) != end && *std::next(it) == '}') {
      oss << '}';
      std::advance(it, 2);
    } else {                                                                     // Regular character, just gets writed out
      oss << *it;
      ++it;
    } 
  }
  
  // Check for leftover args
  if (idx < n)
    throw std::runtime_error("Too Many arguments for format string");
   
  // print out the fmt
  std::cout << oss.str();
}

/**
 * @brief Prints a formatted line (with newline) using `{}` placeholders.
 *
 * Same behavior as `print()` but appends a newline to the output.
 *
 * @tparam Args  Variadic argument types
 * @param fmt    Format string
 * @param args   Arguments to interpolate into `{}` placeholders
 */
template <typename... Args>
inline void println(std::string_view fmt, const Args&... args) {
  print(fmt, args...);
  std::cout << '\n';
}
