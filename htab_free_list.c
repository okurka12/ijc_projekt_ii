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
#include <assert.h>
#include <stdio.h>   // vypisy
#include <stdlib.h>  // free


void htab_free_list(htab_ele_t *list) {
    assert(list!=NULL);
    logv("FUN: zavolan free list s %p", (void *)list);

    htab_ele_t *next = list;
    htab_ele_t *element = list;
    size_t i = 0;
    do {
        next = element->next;
        logv("MEM: uvolnuji %lu. prvek seznamu na %p", i, (void *)element);
        htab_key_dtor(element);
        free(element);
        element = next;
        i++;
    } while (element != NULL);
}
