#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=test

cd "${SCRIPT_BASEDIR}/.."

mkdir -p "build_${BUILD_TYPE}"
cd "build_${BUILD_TYPE}"
pwd

set -e

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
make -j 4

cd bin

./test --libidentify
echo "status: $?"

./test --list-tests || true
echo "status: $?"

./test --abort --durations yes
echo "status: $?"
