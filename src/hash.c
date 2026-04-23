#include "hash.h"
#include "utils.h"

static hash_t crc_table[256];

static void hash_crc32_init();

hash_t hash_const(ATTR_UNUSED char* str, ATTR_UNUSED size_t len)
{
  return 0;
}

hash_t hash_len(ATTR_UNUSED char* str, size_t len)
{
  return (hash_t)len;
}

hash_t hash_ascii_sum(char* str, size_t len) 
{
  hash_t hsum = 0;

  for (size_t i = 0; i < len; ++i) 
    hsum += (hash_t)str[i];

  return hsum;
}

hash_t hash_shift_left(char* str, size_t len)
{
  hash_t hash = 0;

  for(size_t i = 0; i < len; ++i)
    hash = (hash << 1) ^ (hash_t)str[i];

  return hash;
}

hash_t hash_shift_right(char* str, size_t len)
{
  hash_t hash = 0;

  for(size_t i = 0; i < len; ++i)
    hash = (hash >> 1) ^ (hash_t)str[i];

  return hash;
}


hash_t hash_gnu(char* str, size_t len)
{
  hash_t hash = 5381;

  for(size_t i = 0; i < len; ++i) 
    hash = (hash << 5) + hash + (hash_t)str[i];

  return hash;
}

hash_t hash_djb2(char* str, size_t len)
{
  hash_t hash = 0;
  for(size_t i = 0; i < len; ++i)
    hash = (hash << 5) + hash + (hash_t)str[i];

  return hash;
}

hash_t hash_crc32(char* str, size_t len)
{
	hash_t crc32 = 0xFFFFFFFFu;

	if (crc_table[255] == 0)
		hash_crc32_init();
	
	for (size_t i = 0; i < len; i++) {
		crc32 ^= (hash_t)str[i];
		crc32 = (crc32 >> 8) ^ crc_table[crc32 & 0xFF];
	}
	
	crc32 ^= 0xFFFFFFFFu;
	return crc32;
}

static void hash_crc32_init()
{
	uint32_t crc32 = 1;
	for (size_t i = 128; i; i >>= 1) {
		crc32 = (crc32 >> 1) ^ (crc32 & 1 ? 0xedb88320 : 0);
		for (size_t j = 0; j < 256; j += 2*i)
      crc_table[i + j] = crc32 ^ crc_table[j];
	}
}
