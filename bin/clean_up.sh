#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=${BUILD_TYPE:-release}

cd "${SCRIPT_BASEDIR}/.."

rm -rf build_debug build_release build_test
rm -rf tmp/wallet tmp/html
