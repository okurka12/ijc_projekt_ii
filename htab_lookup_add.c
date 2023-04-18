/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-13  **
**              **
** Last edited: **
**  2023-04-18  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab_priv.h"
#include <stdio.h>  // vypisy chyb
#include <stdlib.h>  // malloc key
#include <string.h>  // strcpy strlen atd


htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    logv("FUN: zavolan htab_lookup_add s '%s'", key);

    // podiva se jestli zaznam uz v tabulce je
    htab_ele_t *element = htab_find_element(t, key);
    if (element != NULL) {
        logv(
            "LOG: inkrementuji v tabulce %p heslo '%s' z %d na %d", 
            (void *)t, 
            key, 
            element->kvpair.value, 
            element->kvpair.value + 1
        );
        element->kvpair.value++;
        return &(element->kvpair);
    }

    // pokud tam neni, nasleduje tento kod
    logv("LOG: pridavam do tabulky %p zaznam s klicem '%s'", (void *)t, key);
    t->size++;

    // alokace prvku seznamu
    htab_ele_t *new_element = malloc(sizeof(htab_ele_t));
    logv("MEM: alokovan htab_ele_t na %p", (void *)new_element);
    malloc_null_check(new_element);

    // alokace + kopirovani klice 
    char *new_key = malloc((strlen(key) + 1) * sizeof(char));
    if (new_key == NULL) {
        free(new_element);
        print_malloc_err();
        return NULL;
    }
    strcpy(new_key, key);
    logv("MEM: alokace klice '%s' na %p", key, (void *)new_key);

    // lokalni prvek seznamu, ktery pak vlozim do dynamicke pameti
    htab_ele_t local_element = { 
        .next = NULL, 
        .kvpair.key=new_key, 
        .kvpair.value = 1 
    };

    *new_element = local_element;
    
    // seznam na pozici dane hashem klice
    size_t index = get_index(t, key);
    element = t->arr[index];

    // pokud na pozici v tabulce dane hashem klice neni pritomen seznam
    if (element == NULL) {
        t->arr[index] = new_element;
        return &(new_element->kvpair);

    // pokud tam seznam pritomen je    
    } else {

        // iterace pres prvky seznamu
        while (strcmp(element->kvpair.key, key) && element->next != NULL) {
            element = element->next;
        }

        // pridani noveho prvku na konec seznamu
        element->next = new_element;
        return &(new_element->kvpair);
    }
}
