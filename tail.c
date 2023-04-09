/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-09  **
**              **
** Last edited: **
**  2023-04-09  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximalni delka radku vcetne LF na konci
#define LEN_LIM 4096


// hlavni struktura circular bufferu
typedef struct {

    // pocet ulozenych radku
    unsigned int length;

    // ukazovatko na to kolikaty radek je zrovna zacatek
    unsigned int position;

    // pole radku (retezcu - char *)
    char ** lines;

} cb_t;


/* vrati ukazatel na alokovanou strukturu cb o velikosti n
   pri selhani alokace vraci NULL */ 
cb_t *cb_create(unsigned int n) {

    // alokace samotne struktury
    cb_t *cb = malloc(sizeof(cb_t));

    // null check
    if (cb == NULL) {
        return NULL;
    }

    // inicializace metadat struktury
    cb->length = n;
    cb->position = 0;

    // alokace pole ukazatelu na radky
    cb->lines = malloc(n * sizeof(char *));

    // null check
    if (cb->lines == NULL) {
        return NULL;
    }

    // alokace n radku
    for (unsigned int i = 0; i < n; i++) {

        // alokace i-teho radku
        cb->lines[i] = malloc(LEN_LIM * sizeof(char));

        //null check
        if (cb->lines[i] == NULL) {
            return NULL;
        }

        // prvni null byte, at je to prazdny retezec
        cb->lines[i][0] = '\0';
    }

    return cb;        
}


/* postupne uvolni vsechny naalokovane prvky struktury 
   a pak strukturu samotnou */
void cb_free(cb_t *cb) {

    // POZNAMKA: u dilcich prvku struktury nebudu ty ukazatele 
    // nastavovat na NULL protoze stejne se k nim nebude jak dostat
    
    // uvolneni radku 
    for (unsigned int i = 0; i < cb->length; i++) {
        free(cb->lines[i]);
    }

    // uvolneni pole radku
    free(cb->lines);

    // uvolneni struktury - to uz na NULL nastavim
    free(cb);
    cb = NULL;
}


int main() {
    printf("nazdarek svete\n");

    // toto je jen demonstrace ze to funguje a neleakuje
    cb_t *muj_buffer = cb_create(1000000);
    cb_free(muj_buffer);
    return 0;
}

// TODO
// cb_create(n)    - check
// cb_put(cb,line) -
// cb_get(cb)      -
// cb_free(cb)     - check
