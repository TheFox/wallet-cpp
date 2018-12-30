# WalletCpp

A spreadsheet likewise C++17 library to track your finances.

## Why this project?

_The original idea is from my [ruby Wallet project](https://github.com/TheFox/wallet). This project is rewritten in C++._

While conventionally programs like Microsoft Excel or [LibreOffice](https://www.libreoffice.org/) use [proprietary file formats](https://en.wikipedia.org/wiki/Proprietary_format) and [binary files](https://en.wikipedia.org/wiki/Binary_file) to store your data, this program uses [YAML](https://en.wikipedia.org/wiki/YAML). YAML is a human-readable data serialization format. This means you can edit the YAML files on any [operating system](https://en.wikipedia.org/wiki/Operating_system) with any text editor.

## Features

- Save revenues/expenses entries monthly.
- List saved entries.
- Generate HTML summary.

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

### Install dependencies on Debian 9

```bash
sudo apt-get install --no-install-recommends libboost-filesystem-dev libboost-program-options-dev libboost-date-time-dev
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

## Install via Debian repository

Only Debian 9 (stretch) is supported.

Add the public GPG key to the apt sources keyring:

```bash
wget -qO - https://fox21.at/christian_mayer.asc | sudo apt-key add -
```

Verify key on the keyring. This should print out informations about the key:

```bash
apt-key list 2814B4288C4594FF0BA75571F96ED997C9382D47
```

Add apt source file and update:

```bash
echo 'deb https://debian.fox21.at/ stretch main' > /etc/apt/sources.list.d/fox21at.list
apt-get update
```

Install the package:

```bash
sudo apt-get install wallet-cpp
```

Now you can run the program:

```bash
wallet --help
```

## Install under Debian via .deb file

Go to the [GitHub releases page](https://github.com/TheFox/wallet-cpp/releases) and download the desired version file. Then run:

```bash
sudo dpkg --install wallet-cpp.deb
```

## Tested under

- macOS 10.13 High Sierra
- macOS 10.14 Mojave

## Builded with

- GCC 6.3.0
- GCC 4.2.1 Compatible Clang 6.0.0
- GCC 4.2.1 Compatible Apple LLVM 10.0.0

## Project Links

- [Blog Post about Wallet written in Ruby](http://blog.fox21.at/2015/07/09/wallet.html)

## Similar Projects

- [Wallet written Ruby](https://github.com/TheFox/wallet)

## License

Copyright (C) 2018 Christian Mayer <https://fox21.at>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
