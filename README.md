# Paradox-Platform
Standard headers, code, and files for paradox libraries and software

[![C/C++ Unit Testing](https://github.com/ParadoxGene/Paradox-Platform/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/ParadoxGene/Paradox-Platform/actions/workflows/c-cpp.yml)

[Community Discord](https://discord.gg/KcVBu4n9TU)

# Prerequisites
- C compiler that supports C11 standard or higher.
- C++ compiler that supports C++11 standard or higher.

# Building the library & Running tests
To check if the header files are supported on your system.

Build the shared library:
```
make
```

The c framework shared library will be in `build/paradox-platform/c_framework`

The c++ framework shared library will be in `build/paradox-platform/cpp_framework`

Build the tests:
```
make build_tests
```

Running C Tests
```
./build/paradox-platform-c-unit-tests/Debug/c_unit_tests
```

Running C++ Tests
```
./build/paradox-platform-cpp-unit-tests/Debug/cpp_unit_tests
```

Running Swift Tests
```
W.i.P.
```
