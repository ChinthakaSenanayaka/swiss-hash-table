/**
 * Load factor utility functions.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/

#include "../HashTableData.c"

#ifndef __LoadFactorUtil_C__
#define __LoadFactorUtil_C__

/** 
 * Set the initial hash table load factor.
 * 
 * Input:
 *  numberOfElements - number of elements to be inserted.
 *  currentTableSize - current hash table size.
 * 
 * Output:
 */
void setCurrentLoadFactor(int numberOfElements, unsigned int currentTableSize) {
    currentLoadFactor = (float) numberOfElements / currentTableSize;
}

/** 
 * Update the current hash table load factor.
 * 
 * Input:
 *  numberOfElements - number of elements to be inserted.
 *  currentTableSize - nurrent hash table size.
 * 
 * Output:
 */
void updateCurrentLoadFactor(signed int numberOfElements, unsigned int currentTableSize) {
    currentLoadFactor += (float) numberOfElements / currentTableSize;
}

#endif