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

#include "htab_priv.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


htab_t *htab_init(const size_t n) {

    // alokace mista pro samotnou tabulku (struct) + malloc null check
    htab_t *output = malloc(sizeof(htab_t));
    malloc_null_check(output);
    logv("MEM: alokace htab_t na %p", (void *)output);
    
    // alokace pole ukazatelu na prvky tabulky + malloc null check
    output->arr = malloc(n * sizeof(htab_pair_t *));
    logv("MEM: alokace htab_t->arr (htab_ele_t**) na %p", (void *)output->arr);
    if (output->arr == NULL) {
        free(output);
        print_malloc_err();
        return NULL;
    }

    // inicializace prvku tabulky na null
    for (size_t i = 0; i < n; i++) {
        output->arr[i] = NULL;
    }

    // inicializace metadat tabulky
    output->size = 0;
    output->arr_size = n;

    return output;
}

/* vrati polozku seznamu, ktera obsahuje zaznam (htab_pait_t) nebo NULL */
htab_ele_t *htab_find_element(const htab_t *t, htab_key_t key) {

    size_t index = get_index(t, key);
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


/* vynuluje klic prvku seznamu a uvolni ho, vynuluje hodnotu */
void zero_out_free(htab_ele_t *element){

    // dynamicky alokovany retezec
    htab_key_t key_ptr = element->kvpair.key;

    // vynulovat retezec (bezpecnost)
    memset((char *)key_ptr, 0, strlen(key_ptr));

    // uvolnit retezec
    logv(
        "MEM: uvolnuji klic '%s' na adrese %p", 
        element->kvpair.key, 
        (void *)element->kvpair.key
    );
    free((char *)key_ptr);
    key_ptr = NULL;

    // vynulovat hodnotu (bezpecnost)
    element->kvpair.value = 0;
}


char htab_erase(htab_t *t, htab_key_t key) {
    logv("LOG: odstranuji z tabulky %p zaznam s klicem '%s'", (void *)t, key);

    // ujistit se ze prvek v te tabulce je
    if (htab_find(t, key) == NULL) {
        return 0;
    }

    // index
    size_t index = get_index(t, key);

    // pokud je to jediny prvek seznamu
    // poznamka: to je renundantni kontrolovat, ale necham to tady tak
    if (t->arr[index]->next == NULL) {

        zero_out_free(t->arr[index]);

        // uvolnit prvek seznamu
        logv("MEM: free htab_ele_t na %p", (void *)(t->arr + index));
        free(t->arr[index]);
        t->arr[index] = NULL;

        log("LOG: prvek byl hlavicka a zaroven jediny prvek");
        return 1;
    }

    // pokud to neni jediny prvek seznamu
    htab_ele_t *parent = NULL;
    htab_ele_t *child = NULL;
    htab_ele_t *element = NULL;

    parent = element = t->arr[index];
    child = element->next;
    
    // najde v seznamu prvek se zaznamem s klicem `key`
    size_t i = 0;
    while (strcmp(element->kvpair.key, key)) {
        assert(element->next != NULL);

        parent = element;
        element = element->next;
        child = element->next;
        i++;
    }

    zero_out_free(element);
    parent->next = child;

    logv("MEM: free htab_ele_t na %p (byl to %lu. prvek seznamu)", 
        (void *)element, i);
    free(element);

    // pokud to byl prvni prvek seznamu tak je na nej ukazatel v poli tabulky
    // a je potreba to nastavit na potomka smazaneho prvku
    if (i == 0) {
        t->arr[i] = child;
        logv("LOG: jako hlavicka se nastavil potomek %p", (void *)child);
    }
    return 1;  

}

void free_list(htab_ele_t *list) {
    assert(list!=NULL);
    logv("FUN: zavolan free list s %p", (void *)list);

    htab_ele_t *next = list;
    htab_ele_t *element = list;
    size_t i = 0;
    do {
        next = element->next;
        logv("MEM: uvolnuji %lu. prvek seznamu na %p", i, (void *)element);
        zero_out_free(element);
        free(element);
        element = next;
        i++;
    } while (element != NULL);
}

void htab_free(htab_t *t) {
    logv("FUN: zavolano htab_free na %p", (void *)t);

    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr[i] != NULL) {
            logv("FUN: call free_list na indexu %lu (%p)", i, 
                 (void *)(t->arr + i));
            free_list(t->arr[i]);
        }
    }

    logv("MEM: free t->arr (htab_ele_t**) na %p", (void *)t->arr);
    free(t->arr);
    t->arr = NULL;
    logv("MEM: free htab_t na %p", (void *)t);
    free(t);
}

// void htab_clear(htab_t *t) {
//     // iterace pres sezname
//     htab_ele_t *element;
//     for (size_t i = 0; i < t->arr_size; i++) {
//         element = t->arr[i];
//         if (element == NULL) {
//             continue;
//         }


//     }

// }
