#!/bin/bash

cd $(dirname $(realpath ${BASH_SOURCE[0]}))

mkdir -p build
cd build
cmake ..
cmake --build .
cd ..