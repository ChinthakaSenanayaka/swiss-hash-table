/**
 * This is Swiss hash table configurations file.
 * Configurations of the hash table can be controlled from here.
 * 
 * Author: Chinthaka Senanayaka
 * Email: senanayw@mcmaster.ca (senanayakachinthaka@gmail.com)
 * Year: 2025
*/
#ifndef __HashTableConfig_H__
#define __HashTableConfig_H__

// 3 random 64 bit hash values to be used in generating random hash value.
static long long int randomHash1 = 0xff51afd7ed558ccd;
static long long int randomHash2 = 0xc4ceb9fe1a85ec53;
static long long int randomHash3 = 0xd6ac6c112bc703fc;

/** Max load factor value. */
static const float MAX_LOAD_FACTOR = 0.5;

/** Min load factor value. */
static const float MIN_LOAD_FACTOR = MAX_LOAD_FACTOR / 2; // 1/4

/** Hash table resizing factor. */
static const unsigned short RESIZING_FACTOR = 2;

/** Default meta value for empty hash table spots. */
static const signed char EMPTY = (char) -128;

/** Default meta value for deleted hash table spots. */
static const signed char DELETED = (char) -2;

/** Default meta value for sentinel hash table spots. */
static const signed char SENTINEL = (char) -1;

/** Group size for number of slots in a group. */
static const int GROUP_SIZE = 16;

#endif