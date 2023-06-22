# ijc_projekt_ii
The second project for the IJC (The C language) course at FIT BUT. I'm quite happy with how it turned out.
- The course took place in the summer semester of 2022/2023

## Contents:
- `tests` folder - python tests for the first part of the project
  - this is identical code as in my other repo, which I published earlier: https://github.com/okurka12/IJC_project2_tests
- `sources` folder - here I archived the arcticle from Ozan Yigit at York University in Toronto, CA
  - we were supposed to implement a hash function described in this article
  - it couldn't be archived by the Wayback Machine
- `htab.h` - API for the `htab` hash-table library (it was provided in the project assignment)
- `htab_*.c` - implementation of the library
- `tail.c` - simple version of `tail` implemented using a circular buffer 
- `wordcount.c` - the program wordcount implemented using the `htab` library
  - try `make run` for an example usage
- `zadani.txt` - the project assignment

## Assignment:
1. write `tail`
2. implement hash-table library with given API and then write `wordcount`

## Build
- `make` builds everything
  - `tail` - first part of the assignment
  - `wordcount` - second part of the assignment
  - `libhtab.a` - static version of the library
  - `libhtab.so` - dynamic version of the library
- `make run` builds and smoke tests `wordcount`
