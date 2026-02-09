/**
 * Hashing algorithm functions.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
#include "../../HashTableConfig.h"

#ifndef __HashUtil_C__
#define __HashUtil_C__

/**
 * Generates 64 bit hash code.
 * Reference paper:
 *    DOI: https://doi.org/10.48550/arXiv.1202.4961
 *    Name: Strongly universal string hashing is fast
 *    Authors: Daniel Lemire and Owen Kaser
 *    Page: 1637, Appendix 1, Multilinear (2-by-2) (and HM) algorithm C impl
 * 
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
 * Getter for low bit 7 of given 64 bit hash code.
 * 
 * Input:
 *   hashcode - unsigned long 64 but hash code.
 * 
 * Output:
 *   low bit 7 of the hash code. This fits in to a char.
 */
char getLowBits7(unsigned long long int hashcode) {
  return hashcode & 0x7f;
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

/**
 * Hash function (H2).
 */
char getHashVerifierVal(long long int value) {
    char hashVerifierVal = getLowBits7(gen64BitHash(value));
    
    return hashVerifierVal;
}

#endif