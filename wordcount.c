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

#include "htab.h"
#include <stdio.h>

int main() {

    /* demonstrace */
    printf("volam hash a init\n");
    htab_hash_function("ahoj");
    htab_init(5);
    return 0;
}
