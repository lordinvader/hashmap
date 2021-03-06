#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <hashmap.h>
#include <hashfun.h>

#define test(a)\
  fprintf(stderr, "TEST: %50s\tin file: %20s in line: %5d\t", #a, __FILE__, __LINE__); \
  if(a) fprintf(stderr, "PASSED\n");                                     \
  else {\
    fprintf(stderr, "NOT PASSED!!\n");\
    exit(-1);\
  }

static void test_populate(HashMap* hm);
static void test_depopulate(HashMap* hm);
static void test_count_empty();

int main(void)
{
  HashMap* hm = HashMap_new(NULL, NULL);

  test_count_empty();
  
  test_populate(hm);

  test_depopulate(hm);
  
  HashMap_free(hm);
  return 0;
}

static void test_count_empty()
{
  test(HashMap_count(HashMap_new(NULL, NULL))==0);
}

static void test_populate(HashMap* hm)
{
  long n = 1000000;
  long i;

  for(i=0; i<=n; i++)
    HashMap_insert(hm, (void*)i, (void*)i);

  test(HashMap_count(hm)==n);
}

static void test_depopulate(HashMap* hm)
{
  long n = HashMap_count(hm);
  long i;

  for(i=0; i<=n; i++)
    HashMap_delete(hm, (void*)i);

  test(HashMap_count(hm)==0);
}

