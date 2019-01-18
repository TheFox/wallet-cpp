#!/usr/bin/env bash

SCRIPT_BASEDIR=$(dirname "$0")


cd "${SCRIPT_BASEDIR}/.."

if [[ ! -f .env ]]; then
	cp .env.example .env
fi
