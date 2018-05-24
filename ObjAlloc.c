/* ObjAlloc class:

   .  "growing" arrays, 
   .  objects can be pushed in the middle of an array

   Eidon (Eidon@tutanota.com), V1.1
 */
#include "ObjAlloc.h"

static int OA_err;

ObjAlloc_t *OA_open(size_t elem_sz)
{
ObjAlloc_t *oa;
void *array;

  if ( (oa=malloc(sizeof(ObjAlloc_t))) == NULL ||
       (array=malloc(OA_BUFFER_SIZE*elem_sz))== NULL )
  {
     return NULL;
  }
  oa->nelem = 0;
  oa->array = array;
  oa->elem_sz = elem_sz;
  oa->allocated = OA_BUFFER_SIZE;
  OA_err=0;
  return oa;
}

int OA_close(ObjAlloc_t *oa)
{
  if (oa == NULL)
      return NULL_PTRS;
  free(oa->array);
  free(oa);
  return OA_err=0;
}

void *OA_array(ObjAlloc_t *oa)
{
  if (oa == NULL)
  {
      OA_err = NULL_PTRS;
      return NULL;
  }
  OA_err=0;
  return oa->array;
}

int OA_cardinality(ObjAlloc_t *oa)
{
  if (oa == NULL)
      return OA_err = NULL_PTRS;
  OA_err=0;
  return oa->nelem;
}

void *OA_insert(ObjAlloc_t *oa, size_t index, void *obj)
{
  size_t nelem, allocated, elem_sz;
  void  *array;

  if (oa == NULL || obj == NULL)
  {
      OA_err = NULL_PTRS;
      return NULL;
  }

  nelem = oa->nelem;
  allocated = oa->allocated;
  array = oa->array;
  elem_sz = oa->elem_sz;

  if (nelem == allocated)
  {
      array = realloc(array, (allocated + OA_BUFFER_SIZE) * elem_sz);
      if (array == NULL)
      {
	  OA_err = COULD_NOT_REALLOC;
	  return NULL;
      }

      allocated += OA_BUFFER_SIZE;
  }

  if (index > nelem)
      {
	  OA_err = INDEX_INCONSISTENCY;
	  return NULL;
      }

  memmove((char*)array+(index+1)*elem_sz, (char*)array+index*elem_sz, (nelem-index)*elem_sz);

  memcpy((char*)array+index*elem_sz, (char*)obj, elem_sz);

  nelem++;

  /* closing */

  OA_err=0;
  oa->nelem = nelem;
  oa->allocated = allocated;
  return oa->array = array;
}

char *OA_error_description()
{
  switch (OA_err)
  {
  case 0: return "No errors detected";
  case NULL_PTRS: return "A pointer parameter is NULL";
  case COULD_NOT_REALLOC: return "A call to realloc() has failed";
  case INDEX_INCONSISTENCY: 
      return "An index cannot be greater than the current cardinality";
  default: return "Unknown error";
  }
}
