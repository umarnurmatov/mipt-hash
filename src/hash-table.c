#include "hash-table.h"

#include <string.h>

#include "dllist.h"

static const ssize_t kListInitCapacity = 1;
static const char* kLogFilaname = "log.txt";

typedef uint32_t hash_t;

hash_t _hash_ascii_sum(char* str, size_t len);

err_t hash_table_ctor(HashTable* hash_tbl, size_t size)
{
  hash_tbl->tbl = (dllist_t*)calloc(size, sizeof(dllist_t));

  if(!hash_tbl->tbl)
    return DLLIST_ALLOC_FAIL;

  for(size_t i = 0; i < size; ++i) {
    dllist_ctor(&hash_tbl->tbl[i], kListInitCapacity, kLogFilaname);
  }

  return DLLIST_NONE;
}

err_t hash_table_add(HashTable* hash_tbl, char* str)
{
  size_t str_len = strlen(str);
  
  hash_t hash = _hash_ascii_sum(str, str_len);
  
  dllist_t* lst = &hash_tbl->tbl[hash % hash_tbl->size];
  ssize_t lst_size = lst->size;

  err_t err = dllist_insert_after(lst, str, lst_size-1);
  if(err != DLLIST_NONE)
    return err;

  return DLLIST_NONE;
}

void hash_table_dtor(HashTable* hash_tbl)
{
  for(size_t i = 0; i < hash_tbl->size; ++i)
    dllist_dtor(&hash_tbl->tbl[i]);

  free(hash_tbl->tbl);
}

hash_t _hash_ascii_sum(char* str, size_t len)
{
  hash_t hsum = 0;

  for(size_t i = 0; i < len; ++i)
    hsum += (hash_t)str[i];

  return hsum;
}
