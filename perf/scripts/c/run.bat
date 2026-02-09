@REM Author: Chinthaka Senanayaka
@REM Year: 2025

mkdir -p build\perf\c
mkdir -p build\perf\c\time\out
del build\perf\c\time\out\logs.txt

@REM Compile the C code
@REM ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
gcc -msse2 -DENV=1 -c ./src/C/hashtable/impl/SwissHashTable.c -o ./build/intel/hashtable.o

@REM Compile the perf C files
@ECHO OFF
for %%f in (perf\c\time\*.c) do (
    gcc ./perf/c/time/%%~nf.c ./build/intel/hashtable.o -o ./build/perf/c/time/%%~nf
)

@REM @REM Run the perf C files
@ECHO OFF
for %%f in (build\perf\c\time\*) do (
    build\perf\c\time\%%~nf > build\perf\c\time\out\log_temp.txt

    @REM Log ouput
    type build\perf\c\time\out\log_temp.txt
    type build\perf\c\time\out\log_temp.txt >> build\perf\c\time\out\logs.txt
    del build\perf\c\time\out\log_temp.txt
)