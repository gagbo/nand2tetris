// Implementation of a hash table for the symbol table of the
// assembler
// Collision handling is done using the bucket implementation of the table.
#ifndef _HACKSYMBOLTABLE_H_
#define _HACKSYMBOLTABLE_H_

#ifndef __STDC_WANT_LIB_EXT2__
#define __STDC_WANT_LIB_EXT2__ 1
#endif  // __STDC_WANT_LIB_EXT2__

#define HASHSIZE 33
#define KEY_NOT_FOUND -9999999999

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list of key-value pairs
typedef struct ST_pair ST_pair;
struct ST_pair {
    ST_pair* next;
    char* key;
    uint32_t value;
};
// Print method, to stderr for debug
void ST_print(ST_pair* p_pair);

// Linked list typedef
typedef struct ST_pair* ST_pairs;
// Linked list interface
void STP_push_back(ST_pairs* list, ST_pair* element);
void STP_pop_front(ST_pairs* list);
ST_pair* STP_front(ST_pairs* list);
ST_pair* STP_back(ST_pairs* list);
void STP_print_all_elements(ST_pairs* p_list);
void STP_delete_list(ST_pairs* list);
// Check if a given key is in the linked list
// This method's output is the value if the key is found,
// or the negative preprocessor constant KEY_NOT_FOUND otherwise.
int64_t STP_check_for_key(ST_pairs* list, const char* wantedKey);

// Struct for the hash table
typedef struct HackSymbolTable HackSymbolTable;
struct HackSymbolTable {
    // This is an array of linked lists
    ST_pairs hash_buckets[HASHSIZE];
};

// Hash function that takes a string and gives an integer in
//   [0..HASHSIZE-1]
// It is this method's responsibility to give a valid hash number in
// the interval
unsigned long ST_hash(const char* key);

// Initialisation of the table
// Put null pointers in the array and populate the 'built-in' assembly
// keywords
void ST_initialise(HackSymbolTable* p_table);
// Check if key is in table.
// To avoid multiple passes, the method should either :
// - directly give the value associated with the key in the table if it exists.
// - return the negative preprocessor constant KEY_NOT_FOUND otherwise.
int64_t ST_check_for_key(HackSymbolTable* p_table, const char* wantedKey);
// Adds a new pair in the hash table
// It is the caller's responsibility to check that the key doesn't already
// exists in the table
void ST_add_key(HackSymbolTable* p_table, const char* newKey,
                const uint32_t value);

// Prints the table on stderr, solely for debug purposes
void ST_print_table(HackSymbolTable* p_table);
void ST_delete_all_entries(HackSymbolTable* p_table);

#endif  // _HACKSYMBOLTABLE_H_
