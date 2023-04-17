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
 * Hlavickovy soubor pro funkci read_word
 */


#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>

/* ze souboru `f` nacte jedno slovo (maximalne `max` - 1 znaku) do bufferu `s`, 
   kdyz dojde na konec souboru, vraci `EOF`, jinak vraci delku slova */
int read_word(char *s, int max, FILE *f);

#endif  // #ifndef _IO_H_
