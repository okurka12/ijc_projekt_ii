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

#include "htab_priv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


htab_t *htab_init(const size_t n) {

    // alokace mista pro samotnou tabulku (struct) + malloc null check
    htab_t *output = malloc(sizeof(htab_t));
    malloc_null_check(output);
    
    // alokace pole ukazatelu na prvky tabulky + malloc null check
    output->arr = malloc(n * sizeof(htab_pair_t *));
    if (output->arr == NULL) {
        free(output);
        print_malloc_err();
        return NULL;
    }

    // inicializace prvku tabulky na null
    for (size_t i; i < n; i++) {
        output->arr[i] = NULL;
    }

    // inicializace metadat tabulky
    output->size = 0;
    output->arr_size = n;

    return output;
}

/* vrati polozku seznamu, ktera obsahuje zaznam (htab_pait_t) nebo NULL */
htab_ele_t *htab_find_element(const htab_t *t, htab_key_t key) {

    size_t index = htab_hash_function(key) % t->arr_size;
    htab_ele_t *element = t->arr[index];

    // kdyz je na pozici dane hashem klice pritomen seznam
    if (element != NULL) {

        // iterace pres prvky seznamu - while dojde bud na prvek se zaznamem
        // s klicem `key` nebo na posledni prvek
        while (strcmp(element->kvpair.key, key) && element->next != NULL) {
            element = element->next;
        }

        // pokud se v seznamu nasel zaznam s klicem `key`
        if (!strcmp(element->kvpair.key, key)) {
            return element;
        
        // jedna o posledni zaznam: zaznam s klicem `key` se nenasel
        } else {
            return NULL;
        }
    
    // na pozici dane hashem klice seznam pritomen neni
    } else {
        return NULL;
    }
}


htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    htab_ele_t *element = htab_find_element(t, key);
    if (element == NULL) {
        return NULL;
    } else {
        return &(element->kvpair);
    }
}


htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {

    // podiva se jestli zaznam uz v tabulce je
    htab_ele_t *element = htab_find_element(t, key);
    if (element != NULL) {
        element->kvpair.value++;
        return &(element->kvpair);
    }

    // pokud tam neni, nasleduje tento kod

    // alokace prvku seznamu
    htab_ele_t *new_element = malloc(sizeof(htab_ele_t));
    malloc_null_check(new_element);

    // alokace + kopirovani klice 
    char *new_key = malloc(strlen(key) * sizeof(char));
    if (new_key == NULL) {
        free(new_element);
        print_malloc_err();
        return NULL;
    }
    strcpy(new_key, key);

    // lokalni prvek seznamu, ktery pak vlozim do dynamicke pameti
    htab_ele_t local_element = { 
        .next = NULL, 
        .kvpair.key=new_key, 
        .kvpair.value = 1 
    };

    *new_element = local_element;
    
    // seznam na pozici dane hashem klice
    size_t index = htab_hash_function(key) % t->arr_size;
    element = t->arr[index];

    // pokud na pozici v tabulce dane hashem klice neni pritomen seznam
    if (element == NULL) {
        t->size++;
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
