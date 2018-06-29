#include <hashfun.h>
#include <string.h>

/*
  Tiene conto dei primi sizeof(double) caratteri
*/
double strhash(char* s)
{
  long
    i,
    res = 0;
  
  for(i=strlen(s)-1; i>=0; i--) {
    res = res<<8;
    res += (long)s[i];
  }

  return (double)res;
}



double addrhash(void* a)
{
  long al = (long)a;
  return (double)al;
}


double longhash(long l)
{
  return (double)l;
}
