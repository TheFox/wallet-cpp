# WalletCpp

A spreadsheet likewise C++17 program to track your finances.

## Why this project?

_The original idea is from my [Ruby Wallet project](https://github.com/TheFox/wallet). This project is rewritten in C++._

While conventionally programs like Microsoft Excel or [LibreOffice](https://www.libreoffice.org/) use [proprietary file formats](https://en.wikipedia.org/wiki/Proprietary_format) and [binary files](https://en.wikipedia.org/wiki/Binary_file) to store your data, this program uses [YAML](https://en.wikipedia.org/wiki/YAML). YAML is a human-readable data serialization format. This means you can edit YAML files on any [operating system](https://en.wikipedia.org/wiki/Operating_system), using any text editor.

## Project Outlines

The project outlines as described in my blog post about [Open Source Software Collaboration](https://blog.fox21.at/2019/02/21/open-source-software-collaboration.html).

- The main purpose of this software is to track revenues and expenses, to have a monthly overview.
- Use YAML file format to be able to commit to Git.
- This software *could* be an invoice generator in the future.
- This list is open. Feel free to request features.

## Features

- Save revenues/expenses entries monthly.
- List saved entries.
- Generate HTML summary: overall, yearly, monthly.
- Graphs using gnuplot.

## Planned Features

- CSV Import
- CSV Export
- Invoices
- Epics

## Documentation

Read more documentation in the [Wiki](https://github.com/TheFox/wallet-cpp/wiki) about

- [**INSTALLATION**](https://github.com/TheFox/wallet-cpp/wiki/Install)
- [**BUILDING**](https://github.com/TheFox/wallet-cpp/wiki/Building)

Further readings:

- [**COMMANDS**](https://github.com/TheFox/wallet-cpp/wiki/Commands)
- [**COOKBOOK**](https://github.com/TheFox/wallet-cpp/wiki/Cookbook)

## Project Links

- [Homepage](https://wallet.fox21.at/)
- [Demo page](https://wallet.fox21.at/demo/)
- [Initial WalletCpp blog post](https://blog.fox21.at/2018/11/02/cpp-smart-pointers.html)
- [Blog Post about Wallet written in Ruby](http://blog.fox21.at/2015/07/09/wallet.html)

## Similar Projects

- [Wallet written Ruby](https://github.com/TheFox/wallet)

## License

Copyright (C) 2018 Christian Mayer <https://fox21.at>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
