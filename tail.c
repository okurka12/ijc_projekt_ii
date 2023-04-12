/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-09  **
**              **
** Last edited: **
**  2023-04-12  **
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
    cb->used = 0;
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
    unsigned int idx;
    if (cb->used != 0) {
        idx = (cb->position + n) % cb->used;
    } else {
        idx = 0;
    }

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

/* vytvori kruhovy buffer, precte zadany file stream, vytiskne poslednich
   n radku. Vraci 0 pri uspechu, vraci 1 kdyz nastane chyba */
int create_read_print(FILE *fh, unsigned int n) {
    cb_t *cb = cb_create(n);

    // flag preteceni radku
    char line_too_long = 0;

    // ALOKACE bufferu pro JEDEN RADEK
    char *current_line = malloc(LEN_LIM * sizeof(char));

    // null check
    if (cb == NULL || current_line == NULL) {
        fprintf(stderr, "Chyba alokace paměti. Ukončuji.\n");
        return 1;
    }

    // ukladani vsech radku do kruhoveho bufferu
    while (fgets(current_line, LEN_LIM, fh) != NULL) {

        // pokud je radek prilis dlouhy, tak nastavit ukazovatko souboru 
        // na zacatek dalsiho radku
        if (strlen(current_line) == LEN_LIM - 1 && 
            current_line[LEN_LIM - 2] != '\n') {

            // dokud nenarazi ve fh na LF, dela nic
            while (fgetc(fh) != '\n') {}
        }

        // ulozeni do cb
        cb_put(cb, current_line);
    }

    // UVOLNENI bufferu pro jeden radek
    free(current_line);

    // vytisknuti
    char *radek;
    for (unsigned int i = 0; i < cb->used; i++) {
        radek = cb_get(cb, i);
        printf("%s", radek);
        if (strlen(radek) == LEN_LIM - 1 && radek[LEN_LIM-2] != '\n') {
            putchar('\n');

            // toto je tu jen aby se to vytisklo na stderr jen jednou
            // normalne bych to tiskl az na konci, neco jako
            // "nektery z radku byl prilis dlouhy", ale zadani je
            // divne specificke:
            //
            // Použijte implementační limit na délku řádku (např. 4095 znaků),
            // v případě prvního překročení mezí hlaste chybu na stderr
            // a pokračujte se zkrácenými řádky.
            if (!line_too_long) {
                fprintf(stderr, "Řádek byl příliš dlouhý "
                        "a nevytiskl se celý\n");
            }

            // flag preteceni radku
            line_too_long = 1;
        }
    }

    // pretekl-li radek
    if (line_too_long) {
        return 1;
    }

    cb_free(cb);

    return 0;
}


int main(int argc, char **argv) {
    char too_many_args  = 0;
    char invalid_option = 0;
    char invalid_arg    = 0;
    char from_file      = 0;
    FILE *fh            = stdin;
    unsigned int filename_idx = 0;

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

    // zjisti se jestli se ma cist ze souboru
    if (argc == 2) {
        from_file = 1;
        filename_idx = 1;
    }
    if (argc == 4) {
        from_file = 1;
        filename_idx = 3;
    }

    // otevre se soubor
    if (from_file) {
        fh = fopen(argv[filename_idx], "r");
    }

    // zkontroluje se jestli se podarilo otevrit
    if (fh == NULL) {
        fprintf(stderr, "Soubor '%s' se nepodařilo otevřít.\n", 
                argv[filename_idx]);
        return 1;
    }

    // vystup funkce koresponduje s navratovym kodem programu
    int return_code = create_read_print(fh, n);
    
    // pokud se otevrel soubor tak se zavre
    if (from_file) {
        fclose(fh);
    }

    return return_code;
}
