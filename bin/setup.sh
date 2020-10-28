#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")


cd "${SCRIPT_BASEDIR}/.."

if [[ ! -f .env ]]; then
	cp .env.example .env
fi

kernel_name=$(uname -s)
echo "Kernel: ${kernel_name}"

if [[ "${kernel_name}" = Linux ]]; then
	# lsb_release -i -s
	# Assumes Debian or Ubuntu.
	sudo apt-get install -y --no-install-recommends libyaml-cpp-dev libboost-filesystem-dev libboost-program-options-dev libboost-date-time-dev
elif [[ "${kernel_name}" = Darwin ]]; then
    brew install boost catch2 termcolor
fi
