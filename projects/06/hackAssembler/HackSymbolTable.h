#ifndef _HACKSYMBOLTABLE_H_
#define _HACKSYMBOLTABLE_H_

#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__

#define HASHSIZE 40
#define KEY_NOT_FOUND -9999999999

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct ST_pair ST_pair;
struct ST_pair {
    ST_pair* next;
    char* key;
    uint32_t value;
};

typedef struct ST_pair* ST_pairs;
// Linked list interface
void STP_push_back(ST_pairs* list, ST_pair* element);
void STP_pop_front(ST_pairs* list);
ST_pair* STP_front(ST_pairs* list);
ST_pair* STP_back(ST_pairs* list);
void STP_delete_list(ST_pairs* list);
// We also need a checker to see if the key is already in the list
int64_t STP_check_for_key(ST_pairs* list, const char* wantedKey);

typedef struct HackSymbolTable HackSymbolTable;
struct HackSymbolTable {
    // This is an array of linked lists
    ST_pairs hash_buckets[HASHSIZE];
};

// Hash table implementation in c for the Symbol table of the Hack Assembler
// - We need a hash function that takes a string and gives an integer in
//   [0..HASHSIZE-1]
unsigned long ST_hash(const char* key);

void ST_initialise(HackSymbolTable* table);
// Should return a negative value if the key does not exist
int64_t ST_check_for_key(HackSymbolTable* table, const char* wantedKey);
// Adds a new pair in the hash table
// It is the caller's responsibility to check that the key doesn't already
// exists
void ST_add_key(HackSymbolTable* table, const char* newKey,
                const uint32_t value);

void ST_delete_all_entries(HackSymbolTable* table);

#endif  // _HACKSYMBOLTABLE_H_
