#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

mkdir -p build/perf/c
mkdir -p build/perf/c/time/out
rm ./build/perf/c/time/out/logs.txt 2>/dev/null

if [ "$#" -gt 0 ]; then
    PROCESSOR_TYPE=$1
else
    PROCESSOR_TYPE="INTEL"
fi

function perfIntel {
    # Compile the C code
    # ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
    gcc -msse2 -DENV=1 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/intel/hashtable.o

    # Compile the perf C files
    for file in perf/c/time/*.c
    do
        fileName=("$(basename "$file")")
        fileNameNoExt=("${fileName[@]%.c}")
        gcc $file ./build/intel/hashtable.o -o ./build/perf/c/time/$fileNameNoExt
    done
}

if [ $PROCESSOR_TYPE == "INTEL" ]; then

    perfIntel

elif [ $PROCESSOR_TYPE == "WASM" ]; then

    # Compile the C code
    # ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
    emcc -fPIC -Wno-implicit-function-declaration -msse2 -msimd128 -DENV=2 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/wasm/hashtable.o
    
    # Compile the perf C files
    for file in perf/c/time/*.c
    do
        fileName=("$(basename "$file")")
        fileNameNoExt=("${fileName[@]%.c}")
        emcc $file ./build/wasm/hashtable.o -o ./build/perf/c/time/$fileNameNoExt.wasm
    done

elif [ $PROCESSOR_TYPE == "ARM" ]; then

    # Compile the C code
    # ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
    gcc -DENV=3 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/arm/hashtable.o

    # Compile the perf C files
    for file in perf/c/time/*.c
    do
        fileName=("$(basename "$file")")
        fileNameNoExt=("${fileName[@]%.c}")
        gcc $file ./build/arm/hashtable.o -o ./build/perf/c/time/$fileNameNoExt
    done

elif [ $PROCESSOR_TYPE == "RISCV" ]; then

    # Compile the C code
    # ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
    gcc -DENV=4 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/riscv/hashtable.o

    # Compile the perf C files
    for file in perf/c/time/*.c
    do
        fileName=("$(basename "$file")")
        fileNameNoExt=("${fileName[@]%.c}")
        gcc $file ./build/riscv/hashtable.o -o ./build/perf/c/time/$fileNameNoExt
    done

else

    perfIntel

fi

# Run the perf C files
suffix="out"
for file in build/perf/c/time/*
do
    if [[ "$file" != *"$suffix" ]]; then

        if [ $PROCESSOR_TYPE == "WASM" ]; then
            # Run the C (perf) code on WASM
            wasmedge ./$file > ./build/perf/c/time/out/log_temp.txt
        else
            ./$file > ./build/perf/c/time/out/log_temp.txt
        fi

        # Log ouput
        cat ./build/perf/c/time/out/log_temp.txt
        cat ./build/perf/c/time/out/log_temp.txt >> ./build/perf/c/time/out/logs.txt
        rm ./build/perf/c/time/out/log_temp.txt
    fi

done
