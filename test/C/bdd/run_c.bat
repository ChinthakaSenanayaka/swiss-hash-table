mkdir -p build\intel\

@REM Compile the C code
@REM ENV IDs: 1=INTEL, 2=WASM, 3=ARM, 4=RISCV
gcc -msse2 -DENV=1 -c src/C/hashtable/impl/SwissHashTable.c -o build/intel/hashtable.o

@ECHO OFF
for %%f in (test\C\bdd\*.c) do (
    echo ===== Compiling and running test file: %%~nf.c =====
    gcc %%f build/intel/hashtable.o -o build/intel/%%~nf
    @REM Run the C (test) code on default Intel processor
    build\intel\%%~nf
)