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
#include <stdio.h>  // makra na vypisy chyb
#include <stdlib.h>  // malloc free


htab_t *htab_init(const size_t n) {
    assert(n > 0);

    // alokace mista pro samotnou tabulku (struct) + malloc null check
    htab_t *output = malloc(sizeof(htab_t));
    malloc_null_check(output);
    logv("MEM: alokace htab_t na %p", (void *)output);
    
    // alokace pole ukazatelu na prvky tabulky + malloc null check
    output->arr = malloc(n * sizeof(htab_ele_t *));
    logv("MEM: alokace htab_t->arr (htab_ele_t**) na %p (%lu B)", 
         (void *)output->arr, n * sizeof(htab_ele_t *));
    if (output->arr == NULL) {
        free(output);
        print_malloc_err();
        return NULL;
    }

    // inicializace prvku tabulky na null
    for (size_t i = 0; i < n; i++) {
        output->arr[i] = NULL;
    }

    // inicializace metadat tabulky
    output->size = 0;
    output->arr_size = n;

    return output;
}