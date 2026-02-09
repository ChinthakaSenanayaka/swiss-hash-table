#!/bin/bash

if [ "$#" -gt 0 ]; then
    PROCESSOR_TYPE=$1
else
    PROCESSOR_TYPE="INTEL"
fi

function testIntel {
    mkdir -p ./build/intel/

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
        # Run the C (test) code on default Intel processor
        ./build/intel/$fileNameNoExt
    done
}

if [ $PROCESSOR_TYPE == "INTEL" ]; then

    testIntel

elif [ $PROCESSOR_TYPE == "WASM" ]; then

    # Compile the C code
    # ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
    # emcc -DENV=2 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/wasm/hashtable.o
    emcc -fPIC -Wno-implicit-function-declaration -msse2 -msimd128 -DENV=2 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/wasm/hashtable.o

    # Run the test C files
    for file in test/C/bdd/*.c
    do
        fileName=("$(basename "$file")")
        echo "===== Compiling and running test file: $fileName ====="
        fileNameNoExt=("${fileName[@]%.c}")
        emcc $file ./build/wasm/hashtable.o -o ./build/wasm/$fileNameNoExt.wasm
        # Run the C (test) code on WASM
        wasmedge ./build/wasm/$fileNameNoExt.wasm
    done

elif [ $PROCESSOR_TYPE == "ARM" ]; then

    mkdir -p ./build/arm/

    # Compile the C code
    # ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
    gcc -DENV=3 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/arm/hashtable.o

    # Run the test C files
    for file in test/C/bdd/*.c
    do
        fileName=("$(basename "$file")")
        echo "===== Compiling and running test file: $fileName ====="
        fileNameNoExt=("${fileName[@]%.c}")
        gcc $file ./build/arm/hashtable.o -o ./build/arm/$fileNameNoExt
        # Run the C (test) code on ARM processor
        ./build/arm/$fileNameNoExt
    done

elif [ $PROCESSOR_TYPE == "RISCV" ]; then

    mkdir -p ./build/riscv/

    # Compile the C code
    # ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
    gcc -DENV=4 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/riscv/hashtable.o

    # Run the test C files
    for file in test/C/bdd/*.c
    do
        fileName=("$(basename "$file")")
        echo "===== Compiling and running test file: $fileName ====="
        fileNameNoExt=("${fileName[@]%.c}")
        gcc $file ./build/riscv/hashtable.o -o ./build/riscv/$fileNameNoExt
        # Run the C (test) code on ARM processor
        ./build/riscv/$fileNameNoExt
    done

else

    testIntel

fi