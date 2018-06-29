#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <hashmap.h>
#include <hashfun.h>

#define assert(a)\
  printf("TEST: %50s\tin file: %20s on line: %5d\t", #a, __FILE__, __LINE__);\
  if(a) printf("PASSED\n");\
  else {\
    printf("NOT PASSED!!\n");\
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
  assert(HashMap_count(HashMap_new(NULL, NULL))==0);
}

static void test_populate(HashMap* hm)
{
  long n = 50;
  long i;

  for(i=0; i<=n; i++)
    HashMap_insert(hm, (void*)i, (void*)i);

  assert(HashMap_count(hm)==n);
}

static void test_depopulate(HashMap* hm)
{
  long n = HashMap_count(hm);
  long i;

  for(i=0; i<=n; i++)
    HashMap_delete(hm, (void*)i);

  assert(HashMap_count(hm)==0);
}

