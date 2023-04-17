/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-13  **
**              **
** Last edited: **
**  2023-04-17  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

/* maximalni delka slova vcetne null bytu */
#define MAX_WORD_LEN 256

/* jakou pouzit velikost tabulky */
#define TABLE_LENGTH 32768  

#include "htab.h"
#include "io.h"
#include <assert.h>
#include <stdio.h>

/* kdyz je definovany tento symbol tak se pouzije tato funkce, vsechny zaznamy
   budou v jednom seznamu, min max i avg budou stejne */
#ifdef TEST_CUSTOM_HASH
size_t htab_hash_function(htab_key_t str) {
    return 1;
}
#endif  // ifdef TEST_CUSTOM_HASH

/* vypise hodnotu zaznamu s klicem `key` */
void print_word(htab_t *t, htab_key_t key) {
    htab_pair_t *kv = htab_find(t, key);

    if (kv == NULL) {
        printf("slovo '%s' neni v tabulce pritomno\n", key);
        return;
    }

    printf("slovo '%s' je v tabulce pritomno %dkrat\n", kv->key, kv->value);
}


void output_line(htab_pair_t *zaznam) {
    printf("%s\t%d\n", zaznam->key, zaznam->value);
}


int main() {

    /* konstrukce tabulky */
    htab_t *storage = htab_init(TABLE_LENGTH);

    /* buffer na cteni slov */
    char buf[MAX_WORD_LEN];

    /* cteni slov dokud se nedojde na konec souboru */
    while (read_word(buf, MAX_WORD_LEN, stdin) != EOF) {
        htab_lookup_add(storage, buf);
    }

    /* zavolani output_line na kazdy prvek */
    htab_for_each(storage, output_line);
    
    /* statistika pokud je def statistika */
    #ifdef STATISTICS
    htab_statistics(storage);
    #endif  // ifdef STATISTICS
    
    /* uvolneni tabulky */
    htab_free(storage);

    /* serepeticky */
    

    /* return 0 */
    return 0;
}
