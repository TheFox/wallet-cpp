#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=${BUILD_TYPE:-release}

cd "${SCRIPT_BASEDIR}/.."

which cmake &> /dev/null || { echo 'ERROR: cmake not found in PATH'; exit 1; }

mkdir -p build_${BUILD_TYPE}
cd build_${BUILD_TYPE}

set -x

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
make -j 4 wallet
