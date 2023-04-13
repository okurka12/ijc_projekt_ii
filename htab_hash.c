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

/**
 * Puvodni implementace teto hash funkce se objevila v projektu `sdbm` (Public
 * domain implementace `dbm`)
 * 
 * vizte:
 * 
 * Wikipedia: DBM (computing)
 * https://en.wikipedia.org/wiki/DBM_(computing)
 * * prevzato 2023-04-13
 * 
 * Ozan Yigit: A collection of non-cryptographic hash functions.
 * http://www.cse.yorku.ca/~oz/hash.html
 * * prevzato 2023-04-13
 * 
 * programmingalgorithms.com: SDBM Hash
 * https://www.programmingalgorithms.com/algorithm/sdbm-hash/c/
 * * prevzato 2023-04-13
 * 
 * Original SBDM source code (github mirror repository)
 * https://github.com/davidar/sdbm/blob/29d5ed2b5297e51125ee45f6efc5541851aab0fb/hash.c#L18-L47
 * * prevzato 2023-04-13
 */

#include "htab_priv.h"

size_t htab_hash_function(htab_key_t str) {
    size_t output = 0;

    for (unsigned int i = 0; str[i] != '\0'; i++) {
        output = str[i] + (output << 6) + (output << 16) - output;
    }

    return output;
}
