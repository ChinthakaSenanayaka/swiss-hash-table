#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

currentPath=$(pwd)

# Installing program dependencies
mkdir -p ./build/perf/cpp/swiss/dependencies/abseil_out/
cd ./build/perf/cpp/swiss/dependencies
git clone https://github.com/abseil/abseil-cpp.git
cd abseil-cpp
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../../abseil_out/
cmake --build . --target install

cd $currentPath