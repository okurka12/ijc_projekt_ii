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


void htab_clear(htab_t *t) {
    logv("FUN: Rusim vsechny zaznamy v tabulce %p", (void *)t);
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr[i] != NULL) {
            logv("FUN: call htab_free_list na indexu %lu (%p)", i, 
                 (void *)(t->arr + i));
            htab_free_list(t->arr[i]);
            t->arr[i] = NULL;
        }
    }
}
