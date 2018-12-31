#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=${BUILD_TYPE:-release}

cd "${SCRIPT_BASEDIR}/.."
project_dir=${PWD}

which cmake &> /dev/null || { echo 'ERROR: cmake not found in PATH'; exit 1; }

mkdir -p build_${BUILD_TYPE}
cd build_${BUILD_TYPE}

set -x

if [[ "${BUILD_TYPE}" = "release" ]]; then
    cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DWALLETCPP_GNUPLOT_SUPPORT=ON ..
else
    cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DWALLETCPP_GNUPLOT_SUPPORT=ON -DPROJECT_INSTALL_PREFIX="${project_dir}" ..
fi

make -j 4 wallet
