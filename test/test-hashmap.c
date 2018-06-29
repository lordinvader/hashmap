#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <hashmap.h>
#include <hashfun.h>

#define assert(a)\
  printf("Test: \t%50s\tin file: %20s\ton line: %5d\t", #a, __FILE__, __LINE__);\
  if(a) printf("PASSED\n");\
  else {\
    printf("NOT PASSED!!\n");\
    exit(-1);\
  }

int main(void)
{
  assert(0==0);
  assert(17*2==34);
  assert(0!=0);
  return 0;
}
