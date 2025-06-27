```markdown
# 🧠 Memory Management Simulator

🚀 A modern C++ simulator that models memory allocation using **First-Fit** and **Best-Fit** strategies. Designed to emulate real-world memory management in operating systems, this project features a runtime strategy switch, stress testing, data export, and optional unit testing via GoogleTest.

---

## ✨ Features

- 🔁 **Allocation Strategies**: Switch between First-Fit and Best-Fit at runtime
- 📊 **Exportable Logs**: Memory block states saved to CSV for analysis
- 🧪 **Random Stress Testing**: Dynamically simulate fragmentation and load
- 💾 **Save/Load State**: Resume memory states using file I/O
- 🧠 **CLI-Based UI**: Intuitive and interactive user interface
- ✅ **Unit Tests**: Written using GoogleTest (via `vcpkg`)
- 🧵 **Modular Design**: Clear separation of core logic and utilities


---

## 🔧 Getting Started

### 📦 Prerequisites

- CMake ≥ 3.16
- C++17 compiler (MSVC, GCC, or Clang)
- [vcpkg](https://github.com/microsoft/vcpkg) (for dependency management)

### 🛠️ Build Instructions

```bash
git clone https://github.com/Opikadash/memory-management-simulator.git
cd MemoryManagementSimulator
cmake -B build
cmake --build build
````

### ✅ Run the Simulator

```bash
./build/simulator
```

---

## 🧪 Running Unit Tests (Optional)

Install GoogleTest using [vcpkg](https://github.com/microsoft/vcpkg):

```bash
vcpkg install gtest
```

Then build with tests:

```bash
cmake -DENABLE_TESTING=ON -B build
cmake --build build
cd build && ctest
```

---

## 📈 Visualize Memory Logs

```bash
python scripts/visualize_memory.py data/memory_log.csv
```

Creates a time-series graph of allocation and fragmentation over time.

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---


---

## ✅ `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.16)
project(MemoryManagementSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include header files
include_directories(include)

# Build core simulator
add_executable(simulator
    src/main.cpp
    src/memory_manager.cpp
)

# GoogleTest-based unit tests
option(ENABLE_TESTING "Enable Unit Tests" ON)
if(ENABLE_TESTING)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
    add_executable(simulator_tests
        tests/test_memory_manager.cpp
        src/memory_manager.cpp
    )
    target_include_directories(simulator_tests PRIVATE include)
    target_link_libraries(simulator_tests GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(simulator_tests)
endif()
````

---



---

## ✅ `LICENSE` (MIT)

```text
MIT License

Copyright (c) 2025 [Opika]

Permission is hereby granted, free of charge, to any person obtaining a copy...
```

---


```

> 📌 Make sure GoogleTest is globally installed or built locally and linked properly.

---




