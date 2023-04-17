/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-17  **
**              **
** Last edited: **
**  2023-04-17  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

/** 
 * Soubor s implementaci read_word
 */

#include "io.h"
#include <stdio.h>
#include <ctype.h>

int read_word(char *s, int max, FILE *f) {

    // first_letter
    int first_let;

    // projizdi to pres bile znaky dokud nenarazi na pismenko
    while (isspace( (char)(first_let = fgetc(f)) ) && first_let != EOF) {}
    
    // bud vrati eof nebo zapise prvni pismenko
    if (first_let != EOF) {
        s[0] = first_let;
    } else {
        return EOF;
    }

    // projizdi dalsi pismenka dokud nenarazi na bile nebo konec souboru
    int i;
    int c;
    for (i = 1; i < max - 1; i++) {

        // je to pismenko
        if (!isspace( (char)(c = fgetc(f)) )) {
            s[i] = c;

        // neni to pismenko
        } else {
            s[i] = '\0';
            break;
        }

        // je to eof
        if (c == EOF) {
            s[i] = '\0';
            break;
        }
    }

    return i;
}