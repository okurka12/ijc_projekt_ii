/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-13  **
**              **
** Last edited: **
**  2023-04-18  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab_priv.h"
#include <stdio.h>  // vypisy chyb
#include <stdlib.h>  // free
#include <string.h>  // memset


void htab_key_dtor(htab_ele_t *element){
    logv(
        "MEM: uvolnuji klic '%s' na adrese %p", 
        element->kvpair.key, 
        (void *)element->kvpair.key
    );

    // dynamicky alokovany retezec (lok. promenna at je to kratsi)
    htab_key_t key_ptr = element->kvpair.key;

    // vynulovat retezec (bezpecnost)
    memset((char *)key_ptr, 0, strlen(key_ptr));

    // uvolnit retezec
    free((char *)key_ptr);
    key_ptr = NULL;

    // vynulovat hodnotu (bezpecnost)
    element->kvpair.value = 0;
}

