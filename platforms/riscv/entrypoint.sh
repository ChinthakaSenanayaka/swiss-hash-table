#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

cd /project
mkdir -p build/riscv

# Compile the C code
# ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
riscv64-unknown-elf-gcc -O2 -march=rv64gcv -DENV=4 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/riscv/hashtable.o

# Run the test C files
for file in test/C/bdd/*.c
do
    fileName=("$(basename "$file")")
    echo "===== Compiling and running test file: $fileName ====="
    fileNameNoExt=("${fileName[@]%.c}")
    riscv64-unknown-elf-gcc -O2 -march=rv64gcv $file ./build/riscv/hashtable.o -o ./build/riscv/$fileNameNoExt
    # Run the C code on RISCV processor QEMU emulator
    qemu-riscv64 -L $RISCV/sysroot ./build/riscv/$fileNameNoExt
done