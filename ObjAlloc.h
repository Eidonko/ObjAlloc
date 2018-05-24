#ifndef _OBJ__ALLOCATION_MANAGER
#define _OBJ__ALLOCATION_MANAGER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OA_BUFFER_SIZE   64

#define NULL_PTRS            -201
#define COULD_NOT_REALLOC    -202
#define INDEX_INCONSISTENCY  -203

typedef
 struct {
	  size_t  nelem;
	  size_t  elem_sz;
	  size_t  allocated;
	  void   *array;
 } ObjAlloc_t;


ObjAlloc_t *OA_open(size_t);

int OA_close(ObjAlloc_t*);

void *OA_array(ObjAlloc_t*);

int OA_cardinality(ObjAlloc_t*);

void *OA_insert(ObjAlloc_t*, size_t, void*);

char *OA_error_description(void);
#endif
