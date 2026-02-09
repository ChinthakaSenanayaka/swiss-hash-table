/**
 * This is C implementation of Swiss hash table. Open addressing and linear probing is used.
 * 
 * Tasks:
 *  1. Design for 1 value insert and search
 *  2. Insert 1 value successfully
 *  3. Search added 1 value successfully
 *  4. Delete 1 value successfully
 *  5. Add nice to have features to the project
 *  6. Add hash table resizing and test for all operations
 *  7. Create byte code for Intel, ARM, RISC-V and WebAssembly
 *  8. SIMD instructions
 *  9. Performance test and results
 * 
 * Moreover, All operations adhere to amortized time complexity O(1) and table resizing amortized time complexity O(2m).
 * Max load factor is 0.50 and Min load factor is 0.25.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include <stdio.h>
#include <stdlib.h>

#include "../SwissHashTable.h"

#include "CreateHashTable.c"
#include "InsertElement.c"
#include "SearchElement.c"
#include "DeleteElement.c"
#include "PrintHashTable.c"