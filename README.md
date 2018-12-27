# WalletCpp

## Dependencies

- [CMake](https://cmake.org/) (For building)
- [Boost](https://www.boost.org/) (Filesystem / DateTime / Program Options)
- [yaml-cpp](https://github.com/jbeder/yaml-cpp) (Data source)
- [mstch](https://github.com/no1msd/mstch) (Mustache for C++: generate HTML files)

### Optional

- [termcolor](https://github.com/ikalnytskyi/termcolor) (Color in Terminal)
- [Catch2](https://github.com/catchorg/Catch2) (Unit tests)
- gnuplot

### Install dependencies on macOS

```
brew install boost yaml-cpp mstch gnuplot
```

## Build from Source

You need a modern C++ compiler that supports C++17 and CMake 3.8 or later.

This will only build the binary.

```bash
./bin/build.sh
```

Then the binary is available in `build_release/bin`.

If you want to install Wallet, run:

```bash
./bin/install.sh
```

## Tested under

- macOS 10.13 High Sierra
- macOS 10.14 Mojave
