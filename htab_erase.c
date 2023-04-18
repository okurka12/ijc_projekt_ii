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
#include <assert.h>
#include <stdio.h>  // vypisy chyb
#include <stdlib.h>  // free
#include <string.h>  // strcmp


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

        htab_key_dtor(t->arr[index]);

        // uvolnit prvek seznamu
        logv("MEM: free htab_ele_t na %p", (void *)(t->arr + index));
        free(t->arr[index]);
        t->arr[index] = NULL;

        log("LOG: prvek byl hlavicka a zaroven jediny prvek");
        t->size--;
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

    htab_key_dtor(element);
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
    t->size--;
    return 1;  

}
