#pragma once

#include <compare.h>
#include <stdbool.h>

typedef double (*HashFun)(void*);

struct hashmap_s;
typedef struct hashmap_s HashMap;

/**
###HashMap* HashMap_new(HashFun hfun, CompareFun keycmp);
  * hfun           funzione che ritorna un double dato un elemento generico
  * keycmp         funzione di comparazione per le chiavi

RETURNS:  
HashMap vuota.
 */
HashMap* HashMap_new(HashFun hfun, CompareFun keycmp);

/**
###void HashMap_free(HashMap* hm);
  * hm         hashmap

POST:  
Libera la memeoria occupata dalla sola hashtable.
 */
void HashMap_free(HashMap* hm);

/**
###bool HashMap_contains(HashMap* hm, void* key);
  * hm           hashmap
  * key          chiave da cercare

RETURNS:  
True se esiste un elemento con chiave key nella hashmap, altrimenti false.
 */
bool HashMap_contains(HashMap* hm, void* key);

/**
###long HashMap_count(HashMap* hm);
  * hm          hashmap

RETURNS:  
Numero di elementi contenuti nella hashmap
 */
long HashMap_count(HashMap* hm);

/**
###void* HashMap_lookup(HashMap* hm, void* key);
  * hm             hashmap
  * key            chiave da ricercare

RETURNS:  
Il valore associato alla chiave se è nella hashmap, altrimenti NULL.
 */
void* HashMap_lookup(HashMap* hm, void* key);

/**
###void HashMap_insert(HashMap* hm, void* key, void* value);
  * hm             hashmap
  * key            chiave da inserire
  * value          valore da associare

POST:  
Se la chiave non è NULL, viene inserita nella hashmap assiandola al valore value.
 */
void HashMap_insert(HashMap* hm, void* key, void* value);

/**
###void HashMap_delete(HashMap* hm, void* key);
* hm               hashmap
* key              chiave da rimuovere

POST:  
Se l'elemento con chiave key è nella hashmap viene rimosso.
 */
void HashMap_delete(HashMap* hm, void* key);

/**
###void** HashMap_values(HashMap* hm);
  * hm            hashmap

RETURNS:  
Array dei valori presenti nella hashmap.
 */
void** HashMap_values(HashMap* hm);

/**
###void** HashMap_keys(HashMap* hm);
  * hm            hashmap

RETURNS:  
Array delle chiavi presenti nella hashmap.
 */

void** HashMap_keys(HashMap* hm);
