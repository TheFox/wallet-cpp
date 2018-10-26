#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=${BUILD_TYPE:-release}

cd "${SCRIPT_BASEDIR}/.."

mkdir -p build_${BUILD_TYPE}
cd build_${BUILD_TYPE}

set -x
sudo make install
