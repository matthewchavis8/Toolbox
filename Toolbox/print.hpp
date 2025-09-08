#pragma once

#include <iostream>
#include <iterator>
#include <string_view>
#include <tuple>
#include <mutex>

/**
 * @file format.hpp
 * @brief Lightweight formatting utilite using vardiac templates
 *
 * Supports C++ 17 and up. Provides 'print' and 'println' for formatting output
 * similar to Pythons print or Rust println.
 */

// Global Mutex lock for multithreaded use
inline std::mutex mux;

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
 * @throws std::cerr if placeholder count doesn't match argument count
 */
template <typename... Args>
inline void print(std::string_view fmt, const Args&... args) {
  // Acquiring Lock from mutex
  std::lock_guard<std::mutex> lock(mux);

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
      if (idx >= n) {
        std::cerr << "[ERROR]: too few args for format string" << '\n';
        return;
      }
      
      // Logic to print the correct element from the tuple when '{}' is encountered
      std::apply(
        [&](const auto&... unpacked) {
          std::size_t container_idx { 0 };
          ((container_idx++ == idx ? output(std::cout, unpacked) : void()), ...);
        }
        , container);
      
      ++idx;
      std::advance(it, 2);
    } 
    else if (*it == '{' && std::next(it) != end && *std::next(it)== '{') {     // Handles escaped braces: '{{}}'
      std::cout.put('{');
      std::advance(it, 2);
    } 
    else if (*it == '}' && std::next(it) != end && *std::next(it) == '}') {    // Handles escaped braces: '{{}}'
      std::cout.put('}');
      std::advance(it, 2);
    } 
    else {                                                                     // Regular characters gets written out
      std::cout.put(*it);
      ++it;
    } 
  }
  
  // Check for leftover args
  if (idx < n) {
    std::cerr << "[ERROR] Too Many arguments for format string" << '\n';
    return;
  }
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
