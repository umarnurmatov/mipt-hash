#pragma once

#include <dllist.h>
#include <stdint.h>

#include "hash.h"

#ifdef _DEBUG

#define HASH_TABLE_DUMP(htbl, err) \
  hash_table_dump(htbl, err, NULL, __FILE__, __LINE__, __func__)

#else

#define HASHHASH_TABLE_DUMP(htbl, err)

#endif

#define HASH_TABLE_INIT_LIST { 0, NULL }

typedef dllist_err_t err_t;

typedef struct {
  uint32_t  size;
  dllist_t* tbl;

} HashTable;

err_t hash_table_ctor(HashTable* hash_tbl, uint32_t size);

err_t hash_table_add(HashTable* hash_tbl, char* str);

char* hash_table_get(HashTable* hash_tbl, char* str);

void hash_table_dtor(HashTable* hash_tbl);

#ifdef _DEBUG

void hash_table_dump(HashTable* hash_table, err_t err, char* msg,
                     const char* filename, int line, const char* funcname);
#endif
