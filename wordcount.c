/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-13  **
**              **
** Last edited: **
**  2023-04-16  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab.h"
#include <assert.h>
#include <stdio.h>


void print_word(htab_t *t, htab_key_t key) {
    htab_pair_t *kv = htab_find(t, key);

    if (kv == NULL) {
        printf("slovo '%s' neni v tabulce pritomno\n", key);
        return;
    }

    printf("slovo '%s' je v tabulce pritomno %dkrat\n", kv->key, kv->value);
}


int main() {

    /* demonstrace */

    /* LEVEL 1 */
    // -------------------------------------------------------------------------
    // htab_t *storage = htab_init(1);
    // htab_lookup_add(storage, "ahoj");
    // print_word(storage, "ahoj");
    // htab_erase(storage, "ahoj");
    // print_word(storage, "ahoj");
    // htab_free(storage);
    // -------------------------------------------------------------------------
    
    /* LEVEL 2 */
    // -------------------------------------------------------------------------
    // htab_t *storage = htab_init(1);
    // htab_lookup_add(storage, "ahoj");
    // htab_lookup_add(storage, "kamo");
    // print_word(storage, "ahoj");
    // print_word(storage, "kamo");
    // htab_erase(storage, "ahoj");
    // htab_erase(storage, "kamo");
    // print_word(storage, "ahoj");
    // print_word(storage, "kamo");
    // htab_free(storage);
    // -------------------------------------------------------------------------

    /* SLOZITA VERZE */
    // -------------------------------------------------------------------------
    // htab_t *storage = htab_init(1);
    // htab_lookup_add(storage, "ahoj");
    // htab_lookup_add(storage, "ahoj");
    // htab_lookup_add(storage, "ahoj");

    // htab_lookup_add(storage, "jak");
    // htab_lookup_add(storage, "jak");

    // htab_lookup_add(storage, "je");

    // assert(htab_find(storage, "ahoj") != NULL);
    // assert(htab_find(storage, "jak") != NULL);
    // assert(htab_find(storage, "je") != NULL);

    // print_word(storage, "ahoj");
    // print_word(storage, "jak");
    // print_word(storage, "je");

    // printf("\nvolam htab erase\n");
    // htab_erase(storage, "ahoj");
    // print_word(storage, "ahoj");
    
    // htab_erase(storage, "jak");
    // print_word(storage, "jak");
    
    // htab_erase(storage, "je");
    // print_word(storage, "je");


    // printf("\nvolam htab free\n");
    // -------------------------------------------------------------------------

    // prvne smazat pres clear a pak uvolnit celou tabulku
    // -------------------------------------------------------------------------
    htab_t *storage = htab_init(100);
    htab_lookup_add(storage, "sla");
    htab_lookup_add(storage, "nanynka");
    htab_lookup_add(storage, "do");
    htab_lookup_add(storage, "zeli");
    htab_lookup_add(storage, "do");
    htab_lookup_add(storage, "zelicka");
    htab_lookup_add(storage, "natrhala");
    htab_lookup_add(storage, "lupeni");
    htab_lookup_add(storage, "lupenicka");
    htab_clear(storage);
    fprintf(stderr, "eyo\n");
    htab_free(storage);
    // -------------------------------------------------------------------------
    
    return 0;
}
