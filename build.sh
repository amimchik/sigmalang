#!/usr/bin/sh

source ./config.sh

if [ ! -d build ]; then
    mkdir build
fi
cmake -B build -S . 
cmake --build build
