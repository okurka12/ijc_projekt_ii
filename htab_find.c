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
