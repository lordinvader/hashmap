#include <hashmap.h>
#include <hashfun.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_THRESHOLD 0.7
#define INSPECTION_FACTOR 5

long sizes_count = 11;
long sizes[] = {11, 503, 911, 1997, 4001, 7919, 16001, 32003, 64007, 122011, 500009};

struct hashmap_node_s {
  void* key;
  void* value;
};
typedef struct hashmap_node_s HMNode;

struct hashmap_s {
  HMNode* nodes;         //tabella
  long count;            //numero di elementi attualmente contenuti
  long size;             //dimensione della tabella
  long sizes_index;      //indice in sizes

  double threshold;      //percentuale di riempimento che triggera un expand
  double insfact;        //fattore moltiplicativo che determina il numero di tentativi per gli inserimenti
  long longseq;          //massimo numero di collisioni registrate
  
  CompareFun cf;
  HashFun hf;
};

/**
###static long inspect(HashMap* hm, void* key);
  * hm                hashmap
  * key               chiave da cercare

RETURNS:  
Indice della chiave cercata all'interno della tabella. Se l'elemento non esiste ritorna -1.
 */
static long inspect(HashMap* hm, void* key);

/**
###static long inspect_free(HashMap* hm, void* key);
  * hm               hashmap
  * key              chiave da inserire

RETURNS:  
Prima posizione disponibile per la chiave key. Se non ci sono posizioni libere viene dimezzato il threshold e ridimensionata la tabella in accordo con il nuovo valore.
 */
static long inspect_free(HashMap* hm, void* key);

/**
###static long map(double key, long i, long size);
  * key            chiave da mappare
  * i              tentativo di inserimento
  * size           grandezza della tabella

RETURNS:  
L'hash calcolato dati la chiave e il tentativo sulla tabella.
 */
static long map(double key, long i, long size);

/**
###static void expand(HashMap* hm);
* hm           hashmap

POST:  
Espande la tabella di un ordine e la rimappa.
 */
static void expand(HashMap* hm);

HashMap* HashMap_new(HashFun hfun, CompareFun keycmp)
{
  HashMap* res = (HashMap*)malloc(sizeof(HashMap));

  res->sizes_index = 0;
  res->size = sizes[res->sizes_index];
  res->count = 0;
  res->threshold = DEFAULT_THRESHOLD;
  res->longseq = 0;
  res->insfact = INSPECTION_FACTOR;

  if(keycmp==NULL) res->cf = (CompareFun)cmpaddr;
  else res->cf = keycmp;
  
  if(hfun==NULL) res->hf = (HashFun)addrhash;
  else res->hf = hfun;

  res->nodes = (HMNode*)malloc(sizeof(HMNode)*res->size);
  res->nodes = (HMNode*)memset(res->nodes, 0, res->size*sizeof(HMNode));
  
  return res;
}

void HashMap_free(HashMap* hm)
{
  free(hm->nodes);
  free(hm);
}

bool HashMap_contains(HashMap* hm, void* key)
{
  return inspect(hm, key)!=-1l;
}

long HashMap_count(HashMap* hm)
{
  return hm->count;
}

void* HashMap_lookup(HashMap* hm, void* key)
{
  long i = inspect(hm, key);

  if(i==-1l) return NULL;
  return hm->nodes[i].value;
}

void HashMap_insert(HashMap* hm, void* key, void* value)
{
  long e;

  if(HashMap_contains(hm, key) || key==NULL) return;
    
  e = inspect_free(hm, key);

  hm->nodes[e].key = key;
  hm->nodes[e].value = value;
  hm->count++;

  while((double)hm->count/(double)hm->size >= hm->threshold)
    expand(hm);
}

void HashMap_delete(HashMap* hm, void* key)
{
  long i = inspect(hm, key);

  if(i==-1l) return;
  
  hm->nodes[i].key = NULL;
  hm->count--;
}

void** HashMap_values(HashMap* hm)
{
  if(hm->count==0) return NULL;
  
  void** res = malloc(sizeof(void*)*hm->count);
  long i, j = 0;

  for(i=0; i<hm->size; i++) {
    if(hm->nodes[i].key!=NULL) res[j++] = hm->nodes[i].value;
  }

  return res;
}

void** HashMap_keys(HashMap* hm) 
{
  if(hm->count==0) return NULL;
  
  void** res = malloc(sizeof(void*)*hm->count);
  long i, j = 0;

  for(i=0; i<hm->size; i++) {
    if(hm->nodes[i].key!=NULL) res[j++] = hm->nodes[i].key;
  }

  return res;
}

static long map(double key, long i, long size)
{
  long h1, h2, res;

  h1 = ((long)key % size)+1;
  h2 = ((long)(7*key) % size)+1;

  res = h1 + i*h2;
  //if(res<0) res *= -1;              really needed?
  
  return res%size;
}

static long inspect(HashMap* hm, void* key)
{
  long i, h;

  for(i=0; i<=hm->longseq; i++) {
    h = map(hm->hf(key), i, hm->size);

    if(hm->nodes[h].key!=NULL && hm->cf(key, hm->nodes[h].key)==0)
      return h;
  }

  return -1l;
}

static long inspect_free(HashMap* hm, void* key)
{
  long i, h;
  
  for(i=0; i<(long)(hm->size*hm->insfact); i++) {
    h = map(hm->hf(key), i, hm->size);
    
    if(hm->nodes[h].key==NULL) {
      if(i>hm->longseq) hm->longseq = i;
      return h;
    }
  }
  
  hm->threshold /= 2.0;
  while((double)hm->count/(double)hm->size >= hm->threshold)
    expand(hm);
  return inspect_free(hm, key);
}

static void expand(HashMap* hm)
{
  long osize = hm->size;
  long i, e;
  HMNode* onodes = hm->nodes;
  
  if(hm->sizes_index==sizes_count-1) {
    hm->size *= 2;
    hm->size++;
  } else {
    hm->sizes_index++;
    hm->size = sizes[hm->sizes_index];
  }

  hm->nodes = (HMNode*)malloc(hm->size*sizeof(HMNode));
  hm->nodes = (HMNode*)memset(hm->nodes, 0, hm->size*sizeof(HMNode));

  for(i=0; i<osize; i++) {
    if(onodes[i].key != NULL) {
      e = inspect_free(hm, onodes[i].key);

      hm->nodes[e].key = onodes[i].key;
      hm->nodes[e].value = onodes[i].value;
    }
  }
  
  free(onodes);
}
