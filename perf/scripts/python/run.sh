#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

mkdir -p build/perf/python
mkdir -p build/perf/python/time/out
rm ./build/perf/python/time/out/logs.txt 2>/dev/null

# Run the Python code
pythonFilesWithPath=$(find perf/python/time/ -name '*.py' -not -path '*perf/python/time/Test*Util*')
for pythonFileWithPath in $pythonFilesWithPath
do
    python3 $pythonFileWithPath
done