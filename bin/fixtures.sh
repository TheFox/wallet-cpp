#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")
WALLETCPP_BIN=./build_debug/bin/wallet
WALLET_PATH=tmp/wallet

cd "${SCRIPT_BASEDIR}/.."
pwd

if [[ ! -f ${WALLETCPP_BIN} ]] ; then
    echo "ERROR: binary file not found: ${WALLETCPP_BIN}"
    exit 1
fi

mkdir -p tmp

# Epics
${WALLETCPP_BIN} -w ${WALLET_PATH} epic --handle epic1 --title Epic1 --bgcolor '#ff0000'
${WALLETCPP_BIN} -w ${WALLET_PATH} epic --handle epic2 --title Epic2 --bgcolor '#ff0000'

# Entries
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test1a -d 2019-1-1 -r 100 -x epic1
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test1b -d 2019-1-2 -e 20  -x epic1
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test1c -d 2019-1-3 -e 25

${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test2a -d 2019-5-1 -r 200 -x epic1
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test2b -d 2019-5-2 -e 10
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test2c -d 2019-5-3 -e 15  -x epic1

${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test1a -d 2020-6-1 -r 100 -x epic2
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test1b -d 2020-6-2 -e 20  -x epic1
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test1c -d 2020-6-3 -e 25

${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test2a -d 2020-7-1 -r 200 -x epic2
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test2b -d 2020-7-2 -e 10
${WALLETCPP_BIN} -w ${WALLET_PATH} add -t test2c -d 2020-7-3 -e 15  -x epic1
