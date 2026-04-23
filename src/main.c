#include "hash-table.h"

int main()
{

  HashTable hash_tbl = HASH_TABLE_INIT_LIST;

  hash_table_ctor(&hash_tbl, 100);

  char* str = "string";
  hash_table_add(&hash_tbl, str);

  HASH_TABLE_DUMP(&hash_tbl, DLLIST_NONE);

  hash_table_dtor(&hash_tbl);

  return 0;
}
