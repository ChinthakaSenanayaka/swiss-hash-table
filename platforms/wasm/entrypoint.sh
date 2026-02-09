#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

source $HOME/.wasmedge/env

cd /emsdk
. ./emsdk_env.sh

cd /project
mkdir -p build/wasm

# Compile the C code
# ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
emcc -fPIC -Wno-implicit-function-declaration -msse2 -msimd128 -DENV=2 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/wasm/hashtable.o

# Run the test C files
for file in test/C/bdd/*.c
do
    fileName=("$(basename "$file")")
    echo "===== Compiling and running test file: $fileName ====="
    fileNameNoExt=("${fileName[@]%.c}")
    emcc $file ./build/wasm/hashtable.o -o ./build/wasm/$fileNameNoExt.wasm
    # Run the C code on any processor with WASM compiler
    wasmedge ./build/wasm/$fileNameNoExt.wasm
done