/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-13  **
**              **
** Last edited: **
**  2023-04-15  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab.h"
#include <stdio.h>
#include <assert.h>

int main() {

    /* demonstrace */

    /* SIMPLIFIED VERZE */
    // -------------------------------------------------------------------------
    // htab_t *storage = htab_init(1);
    // htab_lookup_add(storage, "ahoj");
    // printf(
    //     "slovo '%s' je pritomno %dkrat\n", 
    //     htab_find(storage, "ahoj")->key, 
    //     htab_find(storage, "ahoj")->value
    // );
    // htab_free(storage);
    // -------------------------------------------------------------------------

    /* SLOZITA VERZE */
    // -------------------------------------------------------------------------
    htab_t *storage = htab_init(100);
    htab_lookup_add(storage, "ahoj");
    htab_lookup_add(storage, "ahoj");
    htab_lookup_add(storage, "ahoj");

    htab_lookup_add(storage, "jak");
    htab_lookup_add(storage, "jak");

    htab_lookup_add(storage, "je");

    assert(htab_find(storage, "ahoj") != NULL);
    assert(htab_find(storage, "jak") != NULL);
    assert(htab_find(storage, "je") != NULL);

    printf(
        "slovo '%s' je pritomno %dkrat\n", 
        htab_find(storage, "ahoj")->key, 
        htab_find(storage, "ahoj")->value
    );
    printf(
        "slovo '%s' je pritomno %dkrat\n", 
        htab_find(storage, "jak")->key, 
        htab_find(storage, "jak")->value
    );
    printf(
        "slovo '%s' je pritomno %dkrat\n", 
        htab_find(storage, "je")->key, 
        htab_find(storage, "je")->value
    );

    printf("volam free\n");
    htab_free(storage);
    // -------------------------------------------------------------------------
    
    return 0;
}
