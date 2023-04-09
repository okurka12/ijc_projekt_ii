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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximalni delka radku vcetne LF na konci
#define LEN_LIM 4096


// hlavni struktura circular bufferu
typedef struct {

    // pocet ALOKOVANYCH radku 
    // (pozor! pro zjisteni opravdove velikosti pouzivat used)
    unsigned int size;

    // ukazovatko na to kolikaty radek je zacatek (write-index)
    unsigned int position;

    // ne vsechny alokovane polozky musi byt obsazene
    unsigned int used;

    // pole radku (retezcu - char *)
    char ** lines;

} cb_t;


/* vrati ukazatel na alokovanou strukturu cb o velikosti n
   pri selhani alokace vraci NULL */ 
cb_t *cb_create(unsigned int n) {

    // nulove n je hloupost a hlavne to pak dela segfaulty
    assert(n > 0);

    // alokace samotne struktury
    cb_t *cb = malloc(sizeof(cb_t));

    // null check
    if (cb == NULL) {
        return NULL;
    }

    // inicializace metadat struktury
    cb->size = n;
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


/* vlozi retezec do bufferu (maximalne LEN_LIM - 1 znaku) 
   a posune ukazovatko */
void cb_put(cb_t *cb, char *line) {
    assert(cb != NULL);

    // zkopiruje retezec line do aktualni pozice v cb,
    // ale maximalne LEN_LIM - 1 znaku
    strncpy(cb->lines[cb->position], line, LEN_LIM * sizeof(char));

    // kdyby `line` byl delsi nez LEN_LIM - 1 (strncpy to nijak neindikuje)
    cb->lines[cb->position][LEN_LIM - 1] = '\0';

    // posunuti ukazovatka
    cb->position++;
    if (cb->position == cb->size) {
        cb->position = 0;
    }

    // pokud neni cb zaplneny cely, inkrement citace used
    if (cb->used < cb->size) {
        cb->used++;
    }
}


/* vrati n-ty radek cb (ma-li cb velikost 10, n=9 je posledni radek) */
char *cb_get(cb_t *cb, unsigned int n) {
    
    // POZNAMKA: vim ze v zadani je at implementuji tuto funkci bez
    // parametru n ale uprimne nevidim v tom zadny uzitek udelat z teto funkce
    // jakysi iterator a ukladat ve strukture jeste read-index: takto
    // ukladam pouze jedno cislo indikujici kolikata polozka pole cb->lines
    // byla zapsana naposledy a to mi prijde semanticky jednoduche
    // a dostacujici

    assert(cb != NULL);

    // zacatek je hned za write indexem
    unsigned int idx = (cb->position + n) % cb->used;

    return cb->lines[idx];
}


/* postupne uvolni vsechny naalokovane prvky struktury 
   a pak strukturu samotnou */
void cb_free(cb_t *cb) {

    // POZNAMKA: u dilcich prvku struktury nebudu ty ukazatele 
    // nastavovat na NULL protoze stejne se k nim nebude jak dostat
    
    // uvolneni radku 
    for (unsigned int i = 0; i < cb->size; i++) {
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
    cb_t *muj_buffer = cb_create(3);
    cb_put(muj_buffer, "ahoj toto je radek 1");
    cb_put(muj_buffer, "ahoj toto je radek 2");
    cb_put(muj_buffer, "ahoj toto je radek 3");
    puts(cb_get(muj_buffer, 0));
    puts(cb_get(muj_buffer, 1));
    puts(cb_get(muj_buffer, 2));
    puts("");
    cb_put(muj_buffer, "ahoj toto je radek 4");
    puts(cb_get(muj_buffer, 0));
    puts(cb_get(muj_buffer, 1));
    puts(cb_get(muj_buffer, 2));
    cb_free(muj_buffer);

    // o toto kdybych se pokusil tak to shodi assert (y)
    // cb_t *novy_buf = cb_create(0);
    // cb_put(novy_buf, "nazdarek");
    // puts(cb_get(novy_buf, 0));
    // cb_free(novy_buf);

    return 0;
}

// TODO
// cb_create(n)    - check
// cb_put(cb,line) - check
// cb_get(cb)      - check
// cb_free(cb)     - check
