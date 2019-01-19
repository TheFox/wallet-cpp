#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")

cd "${SCRIPT_BASEDIR}/.."
pwd

which make &> /dev/null || { echo 'ERROR: make not found in PATH'; exit 1; }
which cmake &> /dev/null || { echo 'ERROR: cmake not found in PATH'; exit 1; }

rm -fr build
mkdir -p build
pushd build > /dev/null
pwd

set -e
set -x
cmake ..
make
