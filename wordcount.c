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

#include "htab.h"
#include "io.h"
#include <assert.h>
#include <stdio.h>

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

    htab_t *storage = htab_init(100);
    char buf[MAX_WORD_LEN];
    while (read_word(buf, MAX_WORD_LEN, stdin) != EOF) {
        htab_lookup_add(storage, buf);
    }
    htab_for_each(storage, output_line);
    
    #ifdef STATISTICS
    htab_statistics();
    #endif  // ifdef STATISTICS
    
    htab_free(storage);
    // -------------------------------------------------------------------------
    return 0;
}
