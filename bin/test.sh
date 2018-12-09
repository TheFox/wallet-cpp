#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=test

cd "${SCRIPT_BASEDIR}/.."

mkdir -p build_${BUILD_TYPE}
cd build_${BUILD_TYPE}

set -x
set -e
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
make -j 4 test

cd bin

./test --libidentify
./test --list-tests
./test --abort --durations yes
