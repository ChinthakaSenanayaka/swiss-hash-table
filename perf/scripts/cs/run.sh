#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

mkdir -p build/perf/cs/time/out
rm ./build/perf/cs/time/out/logs.txt 2>/dev/null

# Run the C# code
cd perf/cs/time

dotnet run

cd ../../..