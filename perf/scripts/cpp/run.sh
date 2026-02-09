#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

mkdir -p build/perf/cpp/basic
mkdir -p build/perf/cpp/basic/time/out
rm ./build/perf/cpp/basic/time/out/logs.txt 2>/dev/null

# ============================Basic CPP HT===========================================

echo "Processing basic C++"
# Generate project's make files
cd build/perf/cpp/basic/time
cmake ../../../../../perf/cpp/basic/time

# Compile the C++ code
cmake --build .

# Run the C++ code
cppFilesWithPath=$(find ../../../../../perf/cpp/basic/time -name '*.cc' -not -path '*../../../../../perf/cpp/basic/time/Test*Util*')
for cppFileWithPath in $cppFilesWithPath
do
    cppFile=$(basename $cppFileWithPath)
    fileNameNoExt=("${cppFile[@]%.cc}")
    ./$fileNameNoExt
done

cd ../../../../..

# ============================Basic CPP HT===========================================

mkdir -p build/perf/cpp/swiss
mkdir -p build/perf/cpp/swiss/time/out
rm ./build/perf/cpp/swiss/time/out/logs.txt 2>/dev/null

# ============================Swiss CPP HT===========================================

echo "Processing Swiss C++"
# Generate project's make files
cd build/perf/cpp/swiss/time
cmake ../../../../../perf/cpp/swiss/time -DCMAKE_PREFIX_PATH=../dependencies/abseil_out/

# Compile the C++ code
cmake --build .

# Run the C++ code
cppFilesWithPath=$(find ../../../../../perf/cpp/swiss/time/ -name '*.cc' -not -path '*../../../../../perf/cpp/swiss/time/Test*Util*')
for cppFileWithPath in $cppFilesWithPath
do
    cppFile=$(basename $cppFileWithPath)
    fileNameNoExt=("${cppFile[@]%.cc}")
    ./$fileNameNoExt
done

cd ../../../../..

# ============================Swiss CPP HT===========================================