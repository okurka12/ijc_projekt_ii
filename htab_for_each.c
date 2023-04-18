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


void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    assert(t != NULL);
    htab_ele_t *element;

    // iterace pres obsazena policka t->arr
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr[i] == NULL) {
            continue;
        }

        // iteruje pres seznam
        element = t->arr[i];
        do {
            f(&(element->kvpair));
            element = element->next;
        } while (element != NULL);
    }
}

