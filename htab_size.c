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


size_t htab_size(const htab_t *t) {
    return t->size;
}
