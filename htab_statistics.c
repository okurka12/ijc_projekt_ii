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
#include <stdio.h>


size_t list_len(htab_ele_t *list) {
    if (list == NULL) {
        return 0;
    }

    size_t output = 0;
    htab_ele_t *element = list;
    do {
        element = element->next;
        output++;
    } while (element != NULL);

    return output;
}


void htab_statistics(const htab_t *t) {

    // kolik je v poli seznamu
    size_t occupied = 0;

    // min = 0xffffffffffffffff
    size_t min = 0;
    min = ~min;

    // max = 0
    size_t max = 0;

    // suma pro vypocet avg
    size_t sum = 0;

    float avg;

    size_t length;

    // iterace pres obsazena policka t->arr
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr[i] == NULL) {
            continue;
        }

        length = list_len(t->arr[i]);
        sum += length;
        occupied++;
        if (length < min) {
            min = length;
        }
        if (length > max) {
            max = length;
        }
    }

    // vypocet avg
    avg = (float)sum / (float)occupied;

    // debug log
    logv("htab_stats: occupied: %lu/%lu min=%lu max=%lu avg=%f", occupied, 
         t->arr_size, min, max, avg);

    // tisk na stderr
    fprintf(stderr, "Statistiky pro htab na %p:\n", (void *)t);
    fprintf(stderr, "-Obsazeno pozic:   %lu/%lu\n", occupied, t->arr_size);
    fprintf(stderr, "-Počet záznamů:    %lu\n", t->size);
    fprintf(stderr, "-Nejkratší seznam: %lu\n", min);
    fprintf(stderr, "-Nejdelší seznam:  %lu\n", max);
    fprintf(stderr, "-Průměrná délka:   %.1f\n", avg);
    
}
