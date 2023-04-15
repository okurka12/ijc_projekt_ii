/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
**              **
**   Created:   **
**  2023-04-12  **
**              **
** Last edited: **
**  2023-04-16  **
*****************/
// Fakulta: FIT VUT
// Vyvíjeno s gcc 10.2.1 na Debian GNU/Linux 11

#include "htab.h"

#ifndef HTAB_H_PRIV__
#define HTAB_H_PRIV__

#define MAX_WORD_LEN 256

/* ziskat index (size_t) v poli seznamu (hash klice key) */
#define get_index(table, key) (htab_hash_function(key) %  (table)->arr_size)

/* chybova zprava pri selhani alokace */
#define MALLOC_ERR_MSG "Chyba alokace paměti\n"

/* vypise na stderr chybu */
#define print_malloc_err() \
do {fprintf(stderr, __FILE__ ":%d: " MALLOC_ERR_MSG, __LINE__ );} while (0)

/* TOTO MAKRO OBSAHUJE RETURN, je-li `arg` NULL, zavola return NULL */
#define malloc_null_check(arg) do \
{if ((arg) == NULL) {print_malloc_err(); return NULL;}} while (0)

#ifndef NDEBUG

/* logs plain string */
#define log(msg) fprintf(stderr, __FILE__ ":%03d: " msg "\n", __LINE__)

/* logs variable(s) */
#define logv(msg, ...) fprintf(stderr, __FILE__ ":%03d: " msg "\n", \
                               __LINE__, __VA_ARGS__)

#else  // ifndef NDEBUG

#define log(msg) {}
#define logv(msg, ...) {}

#endif  // ifndef NDEBUG

struct htab_ele {
    htab_pair_t kvpair;
    struct htab_ele *next;
};

typedef struct htab_ele htab_ele_t;

struct htab {

    // pocet zaznamu v tabulce
    size_t size;

    // velikost tabulky (kolik je v tabulce seznamu)
    size_t arr_size;

    // prvky tabulky (pole ukazatelu na prvky htab_ele_t - hlavy seznamu)
    htab_ele_t **arr;
};

#endif  // #ifndef HTAB_H_PRIV__