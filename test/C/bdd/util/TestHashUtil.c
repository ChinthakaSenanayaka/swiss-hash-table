/**
 * Hashing algorithm functions for tests.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "TestHashUtil.h"

#ifndef __TestHashUtil_C__
#define __TestHashUtil_C__

// 3 random 64 bit hash values to be used in generating random hash value.
static long long int randomHash1 = 0xff51afd7ed558ccd;
static long long int randomHash2 = 0xc4ceb9fe1a85ec53;
static long long int randomHash3 = 0xd6ac6c112bc703fc;

/**
 * Generates 64 bit hash code.
 * 
 * Input:
 *   value - 64 bit value to generate hash code.
 * 
 * Output:
 *   unsigned 64 bit hash code
 */
unsigned long long int gen64BitHash(long long int value) {
  int low = (int) value;
  int high = (int)(value >> 32);
  return randomHash1 * low + randomHash2 * high + randomHash3;
}

/**
 * Getter for high bit 57 out of given 64 bit hash code.
 * 
 * Input:
 *   hashcode - unsigned long 64 but hash code.
 * 
 * Output:
 *   High bit 57 of the hash code.
 */
unsigned long long int getHighBits57(unsigned long long int hashcode) {
  return hashcode >> 7;
}

/** 
 * Hash function (H1). Open addressing and linear probing is used.
 * 
 * Input:
 *  value - value to be inserted to hash table.
 * 
 * Output:
 *  hashIndex - hash value as table index.
 */
unsigned int getHashPosVal(long long int value) {
    unsigned int hashPosVal = getHighBits57(gen64BitHash(value));
    
    return hashPosVal;
}

#endif