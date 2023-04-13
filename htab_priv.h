/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-12  **
**              **
** Last edited: **
**  2023-04-12  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab.h"

#ifndef HTAB_H_PRIV__
#define HTAB_H_PRIV__

struct htab_ele {
    htab_pair_t kvpair;
    struct htab_ele *next;
};

typedef struct htab_ele htab_ele_t;

struct htab {

    // pocet zaznamu v tabulce
    size_t size;

    // kapacita tabulky
    size_t arr_size;

    // prvky tabulky (pole ukazatelu na prvky htab_pair_t)
    htab_ele_t **arr;
};

#endif  // #ifndef HTAB_H_PRIV__