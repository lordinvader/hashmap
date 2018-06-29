#include <hashfun.h>
#include <string.h>

/*
  Mappa distanza da una stringa
*/
double strhash(char* s)
{
  char* base = "c";
  
  if(*s=='\0') 
    return 0;
  else
    return strhash(s+1)+(double)strcmp(base, s)*(double)strlen(s);
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
