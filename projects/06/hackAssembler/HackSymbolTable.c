#include "HackSymbolTable.h"

void STP_push_back(ST_pairs* list, ST_pair* element) {
    element->next = NULL;
    if (*list == NULL) {
        *list = element;
        return;
    }
    ST_pairs temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = element;
    return;
}

void STP_pop_front(ST_pairs* list) {
    if (*list == NULL) {
        return;
    }
    ST_pairs prev = *list;
    *list = (*list)->next;
    free(prev->key);
    free(prev);
    return;
}

ST_pair* STP_front(ST_pairs* list) { return *list; }

ST_pair* STP_back(ST_pairs* list) {
    if (*list == NULL) {
        return NULL;
    }
    ST_pairs temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

void STP_delete_list(ST_pairs* list) {
    while (*list != NULL) {
        STP_pop_front(list);
    }
}

int64_t STP_check_for_key(ST_pairs* list, const char* wantedKey) {
    ST_pairs iter = *list;
    while (iter != NULL) {
        if (strcmp(iter->key, wantedKey) == 0) {
            return iter->value;
        }
        iter = iter->next;
    }
    return KEY_NOT_FOUND;
}

// The hash is done using djb2 algorithm
// http://www.cse.yorku.ca/~oz/hash.html
unsigned long ST_hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % HASHSIZE);
}

int64_t ST_check_for_key(HackSymbolTable* p_table, const char* wantedKey) {
    unsigned long hashValue = ST_hash(wantedKey);
    return STP_check_for_key(&p_table->hash_buckets[hashValue], wantedKey);
}

void ST_add_key(HackSymbolTable* p_table, const char* newKey,
                const uint32_t value) {
    unsigned long hashValue = ST_hash(newKey);
    ST_pair* newPair = malloc(sizeof(ST_pair));
    char* newPairKey = strdup(newKey);
    newPair->key = newPairKey;
    newPair->value = value;
    STP_push_back(&p_table->hash_buckets[hashValue], newPair);
}

void ST_delete_all_entries(HackSymbolTable* p_table) {
    for (int i = 0; i < HASHSIZE; ++i) {
        STP_delete_list(&p_table->hash_buckets[i]);
    }
}

void ST_initialise(HackSymbolTable* p_table) {
    for (int i = 0; i < HASHSIZE; ++i) {
        p_table->hash_buckets[i] = NULL;
    }
    ST_add_key(p_table, "R0", 0);
    ST_add_key(p_table, "R1", 1);
    ST_add_key(p_table, "R2", 2);
    ST_add_key(p_table, "R3", 3);
    ST_add_key(p_table, "R4", 4);
    ST_add_key(p_table, "R5", 5);
    ST_add_key(p_table, "R6", 6);
    ST_add_key(p_table, "R7", 7);
    ST_add_key(p_table, "R8", 8);
    ST_add_key(p_table, "R9", 9);
    ST_add_key(p_table, "R10", 10);
    ST_add_key(p_table, "R11", 11);
    ST_add_key(p_table, "R12", 12);
    ST_add_key(p_table, "R13", 13);
    ST_add_key(p_table, "R14", 14);
    ST_add_key(p_table, "R15", 15);
    ST_add_key(p_table, "SCREEN", 16384);
    ST_add_key(p_table, "KBD", 24576);
    ST_add_key(p_table, "SP", 0);
    ST_add_key(p_table, "LCL", 1);
    ST_add_key(p_table, "ARG", 2);
    ST_add_key(p_table, "THIS", 3);
    ST_add_key(p_table, "THAT", 4);
    ST_add_key(p_table, "WRITE", 18);
    ST_add_key(p_table, "END", 22);
    return;
}
