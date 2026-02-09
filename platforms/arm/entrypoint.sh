#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

cd /project
mkdir -p build/arm

# Compile the C code
# ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
arm-none-eabi-gcc -mfloat-abi=softfp -mfpu=neon --specs=rdimon.specs -Wl,--start-group -lgcc -lc -lm -lrdimon -Wl,--end-group -DENV=3 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/arm/hashtable.o

# Run the test C files
for file in test/C/bdd/*.c
do
    fileName=("$(basename "$file")")
    echo "===== Compiling and running test file: $fileName ====="
    fileNameNoExt=("${fileName[@]%.c}")
    arm-none-eabi-gcc -mfloat-abi=softfp -mfpu=neon --specs=rdimon.specs -Wl,--start-group -lgcc -lc -lm -lrdimon -Wl,--end-group $file ./build/arm/hashtable.o -o ./build/arm/$fileNameNoExt
    # Run the C code on ARM processor QEMU emulator
    qemu-arm-static ./build/arm/$fileNameNoExt
done