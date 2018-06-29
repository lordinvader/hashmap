#pragma once

/**
###typedef int (\*CompareFun)(void\*, void*);

Tipo di dato che permette l'utilizzo di funzioni definite dall'utente per ottenere
un ordinamento. Le funzioni di questo tipo devono rispettare i seguenti requisiti
sul valore di ritorno:

  * 0 se $a=b$
  * 1 sel l'ordinamento a,b è accettato
  * -1 se l'ordinamento a,b non è valido
 */
typedef int (*CompareFun)(void* a, void* b);

/**
###static int cmpaddr(void* a, void* b);
   * a      indirizzo da comparare
   * b      indirizzo da comparare

RETURNS:  
Se: a=b, 0; a<b, 1; a>b, -1.
 */
int cmpaddr(void* a, void* b);
