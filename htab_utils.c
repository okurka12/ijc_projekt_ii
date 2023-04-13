/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-13  **
**              **
** Last edited: **
**  2023-04-13  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab_priv.h"
#include <stdio.h>
#include <stdlib.h>


htab_t *htab_init(const size_t n) {

    // alokace mista pro samotnou tabulku (struct) + malloc null check
    htab_t *output;
    if ((output = malloc(sizeof(htab_t))) == NULL) {
        fprintf(stderr, "Chyba alokace paměti\n");
        return NULL;
    }

    // inicializace metadat tabulky
    output->size = 0;
    output->arr_size = 0;

    // alokace pole ukazatelu na prvky tabulky + malloc null check
    output->arr = malloc(n * sizeof(htab_pair_t *));
    if (output->arr == NULL) {
        fprintf(stderr, "Chyba alokace paměti\n");
        return NULL;
    }

    // tady nevim jestli misto inicializace na null bych nemel ty prvky nejak 
    // alokovat ale zatim to tady tak necham a nacommituju vsechnu praci
    for (size_t i; i < n; i++) {
        output->arr[i] = NULL;
    }

    return output;
}
