# WalletCpp

## Dependencies

- [CMake](https://cmake.org/)
- [Boost](https://www.boost.org/)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)

### Optional

- [termcolor](https://github.com/ikalnytskyi/termcolor)
- [Catch2](https://github.com/catchorg/Catch2)

### Install dependencies on macOS

```
brew install boost yaml-cpp
```

## Build from Source

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
