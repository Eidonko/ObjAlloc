#include "ObjAlloc.h"

void main()
{
  ObjAlloc_t *v;
  int i, o;
  int *pi;

  printf("Content-type: text/plain\n\n");

  v = OA_open(sizeof(int));
  if (v==NULL) 
  {
      fprintf(stderr, "%s\n", OA_error_description());
      return;
  }

  for (i=0; i< 200; i++)
  {
     if (OA_insert(v, i, &i) == NULL)
     {
         fprintf(stderr, "%s\n", OA_error_description());
         return;
     }
  }

  pi = OA_array(v);
  if (pi==NULL)
  {
      fprintf(stderr, "%s\n", OA_error_description());
      return;
  }

  for (i=0; i<200; i++)
    if (pi[i] != i)
       {
           fprintf(stderr, "severe inconsistency!\n");
           return;
       }

  printf(
    "Test no.1 OK: checked 200 entries. Currently %d elements in the array\n",
     OA_cardinality(v));

  printf("Inserting integer '999' into v[2].\n");
  i=999;
  if (OA_insert(v, 2, &i) == NULL)
  {
     fprintf(stderr, "%s\n", OA_error_description());
     return;
  }

  pi = OA_array(v);
  if (pi==NULL)
  {
      fprintf(stderr, "%s\n", OA_error_description());
      return;
  }

  for (i=0; i<10; i++)
  {
   printf("v[%3d]==%d\n", i, pi[i]);
  }
  printf(" ...\n");
  for (i=190; i<OA_cardinality(v); i++)
  {
   printf("v[%3d]==%d\n", i, pi[i]);
  }
  if (pi[2]==999 && pi[1]==1 && pi[3] == 2)
     printf("Test no.2 OK. Currently %d elements in the array\n",
     OA_cardinality(v));
  else
     printf("problems have been detected\n");

  OA_close(v);
}
