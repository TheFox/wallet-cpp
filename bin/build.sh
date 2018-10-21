#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")

cd "${SCRIPT_BASEDIR}/.."

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=debug ..
make
