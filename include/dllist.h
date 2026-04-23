#pragma once

#include <stdlib.h>

#ifdef _DEBUG

#define IF_DEBUG(expr) expr

#define DLLIST_DUMP_(dllist, err) \
  dllist_dump(dllist, err, NULL, __FILE__, __LINE__, __func__);

#define DLLIST_DUMP_MSG_(dllist, err, msg) \
  dllist_dump(dllist, err, msg, __FILE__, __LINE__, __func__);

#else  // _DEBUG

#define IF_DEBUG(expr)

#define DLLIST_DUMP_(dllist, err)

#define DLLIST_DUMP_MSG_(dllist, err)

#endif  // _DEBUG

#define DLLIST_MAKE(varname)         \
  dllist_t varname = {.data  = NULL, \
                      .next  = NULL, \
                      .prev  = NULL, \
                      .free  = 0,    \
                      .cpcty = 0,    \
                      .size  = 0}

typedef char* dllist_data_t;

typedef enum {
  DLLIST_NONE,
  DLLIST_ALLOC_FAIL,
  DLLIST_FIELD_NULLPTR,
  DLLIST_OUT_OF_BOUND,
  DLLIST_NULLPTR,
  DLLIST_BROKEN_NEXT_LOOP,
  DLLIST_INFINIT_NEXT_LOOP,
  DLLIST_BAD_LINK,
  DLLIST_BAD_SIZE,
  DLLIST_BAD_CPCTY,
  DLLIST_SIZE_EXCEED_CPCTY
} dllist_err_t;

typedef struct {
  dllist_data_t* data;

  ssize_t* next;
  ssize_t* prev;

  ssize_t free;

  ssize_t cpcty;
  ssize_t size;

} dllist_t;

dllist_err_t dllist_ctor(dllist_t* dllist, ssize_t init_cpcty,
                         const char* log_filename);

void dllist_dtor(dllist_t* dllist);

dllist_err_t dllist_insert_after(dllist_t* dllist, dllist_data_t val,
                                 ssize_t after);

dllist_err_t dllist_delete_at(dllist_t* dllist, ssize_t at);

dllist_err_t dllist_linearize(dllist_t* dllist);

ssize_t dllist_next(dllist_t* dllist, ssize_t after);

ssize_t dllist_prev(dllist_t* dllist, ssize_t before);

ssize_t dllist_begin(dllist_t* dllist);

ssize_t dllist_end(dllist_t* dllist);

#ifdef _DEBUG
void dllist_dump(dllist_t* dllist, dllist_err_t err, char* msg,
                 const char* filename, int line, const char* funcname);
#endif
