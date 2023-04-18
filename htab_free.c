/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-18  **
**              **
** Last edited: **
**  2023-04-18  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab_priv.h"
#include <stdio.h>   // vypisy
#include <stdlib.h>  // free


void htab_free(htab_t *t) {
    logv("FUN: zavolano htab_free na %p", (void *)t);

    htab_clear(t);

    logv("MEM: free t->arr (htab_ele_t**) na %p", (void *)t->arr);
    free(t->arr);
    t->arr = NULL;
    logv("MEM: free htab_t na %p", (void *)t);
    free(t);
}
