#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

cd /project
mkdir -p build/intel
mkdir -p build/intel/out
rm ./build/intel/out/logs.txt

# Compile the C code
# ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
gcc -msse2 -DENV=1 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/intel/hashtable.o

# Run the test C files
for file in test/C/bdd/*.c
do
    fileName=("$(basename "$file")")
    echo "===== Compiling and running test file: $fileName ====="
    fileNameNoExt=("${fileName[@]%.c}")
    gcc $file ./build/intel/hashtable.o -o ./build/intel/$fileNameNoExt
    # Run the C code on intel
    ./build/intel/$fileNameNoExt > ./build/intel/out/log_temp.txt

    # Log ouput
    cat ./build/intel/out/log_temp.txt
    cat ./build/intel/out/log_temp.txt >> ./build/intel/out/logs.txt
    rm ./build/intel/out/log_temp.txt
done