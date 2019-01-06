#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
BUILD_TYPE=${BUILD_TYPE:-release}

cd "${SCRIPT_BASEDIR}/.."
project_dir=${PWD}

which cmake &> /dev/null || { echo 'ERROR: cmake not found in PATH'; exit 1; }

mkdir -p build_${BUILD_TYPE}
cd build_${BUILD_TYPE}

set -x

if [[ "${BUILD_TYPE}" = "debug" ]]; then
    cmake \
        -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
        -DWALLETCPP_GNUPLOT_SUPPORT=ON \
        -DCMAKE_INSTALL_PREFIX="${project_dir}/tmp/fakeroot" \
        -DPROJECT_SHARE_RESOURCES_PREFIX="${project_dir}/resources" \
        ..
else
    cmake \
        -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
        -DWALLETCPP_GNUPLOT_SUPPORT=ON \
        ..
fi

make -j 4
