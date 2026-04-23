#include "hash-table.h"

#include <string.h>

#include "assertutils.h"
#include "dllist.h"
#include "logutils.h"

static const ssize_t kListInitCapacity = 5;
static const char*   kLogFilaname      = "log.html";

err_t hash_table_ctor(HashTable* hash_tbl, uint32_t size) 
{
  IF_DEBUG(
      utils_assert(kLogFilaname);
      utils_init_log_file(kLogFilaname, LOG_DIR);
  )

  hash_tbl->tbl = (dllist_t*)calloc(size, sizeof(dllist_t));

  if (!hash_tbl->tbl) return DLLIST_ALLOC_FAIL;

  for (size_t i = 0; i < size; ++i) {
    dllist_ctor(&hash_tbl->tbl[i], kListInitCapacity, kLogFilaname);
  }

  hash_tbl->size = size;

  return DLLIST_NONE;
}

err_t hash_table_add(HashTable* hash_tbl, char* str) 
{
  size_t str_len = strlen(str);

  hash_t hash = hash_ascii_sum(str, str_len);

  dllist_t* lst      = &hash_tbl->tbl[hash % hash_tbl->size];
  ssize_t   lst_size = lst->size;

  err_t err = dllist_insert_after(lst, str, lst_size);
  if (err != DLLIST_NONE) return err;

  return DLLIST_NONE;
}

void hash_table_dtor(HashTable* hash_tbl) 
{
  for (size_t i = 0; i < hash_tbl->size; ++i) 
    dllist_dtor(&hash_tbl->tbl[i]);

  free(hash_tbl->tbl);

  IF_DEBUG(
    utils_end_log();
  )
}

#ifdef _DEBUG

void hash_table_dump(HashTable* hash_tbl, err_t err, char* msg,
                     const char* filename, int line, const char* funcname)
{
  for(size_t i = 0; i < hash_tbl->size; ++i) {
    dllist_dump(&hash_tbl->tbl[i], err, msg, filename, line, funcname);
  }
}

#endif

