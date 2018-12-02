# WalletCpp

## Dependencies

- [CMake](https://cmake.org/)
- [Boost](https://www.boost.org/)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)

### Optional

- [termcolor](https://github.com/ikalnytskyi/termcolor)
- [Catch2](https://github.com/catchorg/Catch2) (Unit tests)

### Install dependencies on macOS

```
brew install boost yaml-cpp
```

## Build from Source

You need a modern C++ compiler that supports C++17 and CMake 3.7 or later.

This will only build the binary.

```bash
./bin/build.sh
```

Then the binary is available in `build_release/bin`.

After building the project, run:

```bash
./bin/install.sh
```

## Tested under

- macOS 10.13 High Sierra
- macOS 10.14 Mojave
