#!/usr/bin/sh
set -e

source ./config.sh

if [ ! -d build ]; then
    mkdir build
fi
cmake -B build -S . 
cmake --build build
