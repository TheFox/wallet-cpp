#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=${BUILD_TYPE:-release}

cd "${SCRIPT_BASEDIR}/.."

which cmake &> /dev/null || { echo 'ERROR: cmake not found in PATH'; exit 1; }

set -x

./bin/build.sh
cd build_${BUILD_TYPE}
sudo make install
