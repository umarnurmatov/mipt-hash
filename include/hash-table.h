#pragma once

#include <stdint.h>
#include <dllist.h>

typedef dllist_err_t err_t;

typedef struct
{
  uint32_t size;
  dllist_t* tbl;

} HashTable;

err_t hash_table_ctor(HashTable* hash_tbl, size_t size);


void hash_table_dtor(HashTable* hash_tbl);
