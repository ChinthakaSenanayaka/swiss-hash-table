mkdir -p build\ASM\intel\

nasm -f elf64 -F stabs -g -o ./build/ASM/intel/intel_hashtable.o ./src/ASM/Main.asm 
ld -o ./build/ASM/intel/intel_hashtable ./build/ASM/intel/intel_hashtable.o
build\ASM\intel\intel_hashtable