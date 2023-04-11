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

    // POZNAMKA: 
    // vim ze v zadani je at implementuji tuto funkci bez
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

    // POZNAMKA: 
    // u dilcich prvku struktury nebudu ty ukazatele 
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


int main(int argc, char **argv) {
    char too_many_args  = 0;
    char invalid_option = 0;
    char invalid_arg    = 0;

    // kdyz je moc argumentu
    if (argc > 4) {
        too_many_args = 1;
    }

    // kdyz je zadan jiny prepinac nez -n
    if (argc > 1 && 
        argv[1][0] == '-' &&
        argv[1][1] != 'n') {

        invalid_option = 1;
    }

    // kdyz je programu dan vice nez jeden argument a prvni nezacina pomlckou
    if (argc > 2 && argv[1][0] != '-') {
        invalid_arg = 1;
    }

    // nespravne pouziti programu - ukonceni
    if (too_many_args || invalid_option || invalid_arg) {
        fprintf(stderr, "Usage: %s [-n NUMBER] [filename]\n", argv[0]);
        return 1;
    }

    // definice n: prozatimni signed int pro kontrolu vstupu
    signed int n_tmp = 10;

    // pokud jsou alespon dva argumenty a prvni je `-n`
    if (argc > 2 && !strcmp(argv[1], "-n")) {

        // sscanf vrati mene nez 1 prectenou polozku - neplatne cislo
        if (sscanf(argv[2], "%i", &n_tmp) != 1) {
            fprintf(stderr, "Invalid number: '%s'\n", argv[2]);
            return 1;
        }

        // sscanf nacetl cislo ale je kladne?
        if (n_tmp < 0) {
            fprintf(stderr, "Number must be positive.\n");
            return 1;
        }

        // kdyz to cislo je 0 tak muj program nemusi nic delat 
        // a muze se uspesne se ukoncit
        if (n_tmp == 0) {
            return 0;
        }
    }

    // pretypovani na unsigned int (v tento moment je jiste ze n_tmp je +)
    unsigned int n = n_tmp;

    return 0;
}

// TODO
// cb_create(n)    - check
// cb_put(cb,line) - check
// cb_get(cb)      - check
// cb_free(cb)     - check
