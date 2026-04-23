#pragma once

#include <stddef.h>
#include <stdint.h>

#include "utils.h"

typedef uint32_t hash_t;
typedef hash_t (*hash_func)(char*,size_t);

hash_t hash_const(ATTR_UNUSED char* str, ATTR_UNUSED size_t len);

hash_t hash_len(ATTR_UNUSED char* str, size_t len);

hash_t hash_ascii_sum(char* str, size_t len);

hash_t hash_shift_left(char* str, size_t len);

hash_t hash_shift_right(char* str, size_t len);

hash_t hash_gnu(char* str, size_t len);

hash_t hash_djb2(char* str, size_t len);

hash_t hash_crc32(char* str, size_t len);
