#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

apt-get update && apt-get -y upgrade
# Installing GCC/C++ compiler
apt-get -y install build-essential manpages-dev g++ git make
apt-get update && apt-get -y install wget
apt-get update && apt-get -y install libssl-dev checkinstall zlib1g-dev

currentPath=$(pwd)

# Installing latest cmake
wget https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5.tar.gz
tar -xzvf cmake-3.31.5.tar.gz
cd cmake-3.31.5/ && ./bootstrap && make && make install

# Installing program dependencies
mkdir ./build/perf/cpp/swiss/dependencies && mkdir ./build/perf/cpp/swiss/dependencies/abseil_out
cd ./build/perf/cpp/swiss/dependencies && git clone https://github.com/abseil/abseil-cpp.git
cd ./build/perf/cpp/swiss/dependencies/abseil-cpp && mkdir build
cd ./build/perf/cpp/swiss/dependencies/abseil-cpp/build && cmake .. -DCMAKE_INSTALL_PREFIX=./build/perf/cpp/swiss/dependencies/abseil_out/
cd ./build/perf/cpp/swiss/dependencies/abseil-cpp/build && cmake --build . --target install

cd $currentPath