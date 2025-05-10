# Project unit-tests

## How to build and run

```bash
./run_tests.sh
```

This script:
1. Creates a `tests/build` directory if needed
2. Runs CMake to configure the build
3. Builds the test executable
4. Runs the tests

## Dependencies

- CMake (version 3.10 or later)
- A C++ compiler with C++11 support (e.g., `g++`, `clang++`)

## Example output

```
Test 1: mnemonic passed
Test 2: arg1 passed
...
All tests passed!
```
