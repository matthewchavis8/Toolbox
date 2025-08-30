## Dependencies

### Required
- **C++ Compiler** with C++17 support  
  - gcc 7+  
  - clang 6+  
  - Visual Studio 2019 or higher  
- **CMake** 3.21+

### Recommended Dependencies

#### Doxygen (with Graphviz) — for documentation
- **Debian/Ubuntu**
  ```bash
  sudo apt-get install doxygen graphviz -y

* **Windows (choco)**

  ```powershell
  choco install doxygen.install graphviz -y
  ```
* **macOS (brew)**

  ```bash
  brew install doxygen graphviz
  ```

#### ccache — to speed up compilation

* **Debian/Ubuntu**

  ```bash
  sudo apt-get install ccache -y
  ```
* **Windows (choco)**

  ```powershell
  choco install ccache -y
  ```
* **macOS (brew)**

  ```bash
  brew install ccache
  ```

#### cppcheck — for static analysis

* **Debian/Ubuntu**

  ```bash
  sudo apt-get install cppcheck -y
  ```
* **Windows (choco)**

  ```powershell
  choco install cppcheck -y
  ```
* **macOS (brew)**

  ```bash
  brew install cppcheck
  ```

#### include-what-you-use — for header cleanup (optional)

* **Debian/Ubuntu**

  ```bash
  sudo apt-get install iwyu -y
  ```
* **Windows**
  Installed with many LLVM/Clang distributions (or build from source)
* **macOS (brew)**

  ```bash
  brew install include-what-you-use
  ```
---
