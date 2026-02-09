/**
 * Delete a given element from the hash table.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/

#include "HashTableStructure.h"

/** 
 * Delete the given value in the given hash table.
 * 
 * Input:
 *  *hashTable - pointer to the hash table to delete value.
 *  value - value to be deleted.
 * 
 * Output:
 *  status - if deleted then 1, otherwise -1.
 */
unsigned int delete(HashTable *hashTable, signed int value);