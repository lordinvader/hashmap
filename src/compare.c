#include <stdlib.h>
#include <compare.h>

int cmpaddr(void* a, void* b)
{
  if(a==b) return 0;
  return a<b ? 1 : -1;
}
