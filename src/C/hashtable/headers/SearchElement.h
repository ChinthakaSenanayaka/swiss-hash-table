/**
 * Search a given element in the hash table.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/

#include "HashTableStructure.h"

/** 
 * Search the given value in the given hash table.
 * 
 * Input:
 *  *hashTable - pointer to the hash table to search value.
 *  value - value to be searched.
 * 
 * Output:
 *  valuePosition - if found the index of the value, otherwise -1.
 */
signed int search(HashTable *hashTable, signed int value);