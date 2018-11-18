#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=test

cd "${SCRIPT_BASEDIR}/.."

mkdir -p build_${BUILD_TYPE}
cd build_${BUILD_TYPE}

set -x
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} --target test ..
make -j 4
