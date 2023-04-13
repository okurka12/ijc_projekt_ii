// htab.h - Public domain rozhraní knihovny htab (řešení IJC-DU2)

// následující řádky zabrání násobnému vložení:
#ifndef HTAB_H__
#define HTAB_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool

// Tabulka:
struct htab;    // neúplná deklarace struktury - uživatel nevidí obsah
typedef struct htab htab_t;     // typedef podle zadání

// Typy:
typedef const char * htab_key_t;        // typ klíče
typedef int          htab_value_t;      // typ hodnoty

// Dvojice dat v tabulce:
typedef struct htab_pair {
    htab_key_t    key;          // klíč
    htab_value_t  value;        // asociovaná hodnota
} htab_pair_t;                  // typedef podle zadání

// Rozptylovací (hash) funkce (stejná pro všechny tabulky v programu)
// Pokud si v programu definujete stejnou funkci, použije se ta vaše.
size_t htab_hash_function(htab_key_t str);

// Funkce pro práci s tabulkou:

/* konstruktor tabulky: vrati ukazatel na dynamicky alokovanou tabulku
   nebo NULL pokud selze alokace/dojde k chybe */
htab_t *htab_init(const size_t n);

/* vrati kolik je v tabulce zaznamu */
size_t htab_size(const htab_t * t);

/* vrati kolik je kapacita tabulky */
size_t htab_bucket_count(const htab_t * t);     // velikost pole

/* vrati ukazatel na prvek tabulky dany klicem key nebo NULL kdyz neni */
htab_pair_t * htab_find(const htab_t * t, htab_key_t key);

/* da do tabulky zaznam s klicem key */
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key);

/* rusi zadany zaznam */
bool htab_erase(htab_t * t, htab_key_t key);

// for_each: projde všechny záznamy a zavolá na ně funkci f
// Pozor: f nesmí měnit klíč .key ani přidávat/rušit položky
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data));

/* rusi vsechny zaznamy */
void htab_clear(htab_t * t);

/* destruktor tabulky */
void htab_free(htab_t * t);

// výpočet a tisk statistik délky seznamů (min,max,avg) do stderr:
void htab_statistics(const htab_t * t);

#endif // HTAB_H__