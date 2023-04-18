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

/** 
 * 
 * Proc jsem zvolil 32 768?
 * - U takove velikosti mi zacaly vychazet velice vyrovnane seznamy
 * - Je to asi 260 kB pole, coz je dost, na to ze to jsou jen ukazatele, ale
 *   za to, ze se nemusi cestovat skrz seznamy, je to IMO dobra cena
 * 
 * Vysledky pro 654936 slov v `wamerican-insane 2019.10.06-1`
 * -Obsazeno pozic:   32768/32768
 * -Pocet zaznamu:    654936
 * -Nejkratsi seznam: 4
 * -Nejdelsi seznam:  41
 * -Prumerna delka:   20.0
 * 
 * I mean 655 000 slov. To jsou dobre vysledky, ale je fakt, ze kdyz to bude
 * akorat wordcount nejakeho 1kB textoveho dokumentu, tak alokovat 260 kB
 * jen na ukazatele na hlavicky seznamu je hodne.
 * 
*/

#include "htab.h"
#include "io.h"
#include <assert.h>
#include <stdio.h>

/* kdyz je definovany tento symbol tak se pouzije tato funkce, vsechny zaznamy
   budou v jednom seznamu, min max i avg budou stejne */
#ifdef HASHTEST
size_t htab_hash_function(htab_key_t str) {
    return 1;
}
#endif  // ifdef HASHTEST

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
    int delka;
    char was_warned = 0;
    while ((delka = read_word(buf, MAX_WORD_LEN, stdin)) != EOF) {

        // pridani do tabulky
        htab_lookup_add(storage, buf);

        // varovani zkraceni radku
        if ((delka == MAX_WORD_LEN - 1) && !was_warned) {
            fprintf(stderr, "Řádek byl příliš dlouhý (>= 255 znaků) a byl "
            "zkrácen. Další dlouhé řádky budou také zkráceny.\n");
            was_warned = 1;
        }
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
