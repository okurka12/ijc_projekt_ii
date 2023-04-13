# Vit Pavlik
# login: xpavli0a
# osobni cislo: 251301
# fakulta: FIT VUT
# Created:  2022-04-03
# Modified: 2022-04-03
# vyvijeno s GNU Make 4.3 (Built for x86_64-pc-linux-gnu)

AR=ar
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
# CFLAGS=-m32 -O0 -std=c11 -Wall -Wextra -pedantic -g

# START_test_only
PYTHON=python3
# STOP_test_only

# make
.PHONY: all
all: tail wordcount wordcount-dynamic libhtab.a libhtab.so

# tail executable
tail: tail.c
	$(CC) $(CFLAGS) -o tail tail.c

# static library (htab means -o libhtab.a)
libhtab.a: htab_hash.o htab_utils.o
	$(AR) r libhtab.a htab_hash.o htab_utils.o

# shared library
libhtab.so: htab_hash.o htab_utils.o
	$(CC) -shared -fPIC -o libhtab.so htab_hash.o htab_utils.o

# wordcount executable (dynamically linked)
wordcount-dynamic: htab_priv.h
	$(CC) $(CFLAGS) -o wordcount wordcount.c

# compile htab hash function module
htab_hash.o: htab_priv.h htab_hash.c
	$(CC) $(CFLAGS) -c -fPIC -o htab_hash.o htab_hash.c

# compile htab utilities module
htab_utils.o: htab_priv.h htab_utils.c
	$(CC) $(CFLAGS) -c -fPIC -o htab_utils.o htab_utils.c

# make clean
.PHONY: clean
clean:
	rm -f *.o *.elf tail wordcount wordcount-dynamic



# START_test_only
test: test_tail
# STOP_test_only



# START_test_only
test_tail: tail
	$(PYTHON) tests/test_tail.py
# STOP_test_only



# START_test_only
# to tady mam abych to co vyvijim u sebe ve sve projektove slozce za testy 
# abych to akorat mohl prcnout na github
copytests:
	cp -a ./tests/. ../projekt_ii_tests/IJC_project2_tests/
#   toto je neco jako gitignore lol
	rm -f -r ../projekt_ii_tests/IJC_project2_tests/__pycache__
	rm -f ../projekt_ii_tests/IJC_project2_tests/tmp.py
# STOP_test_only



# START_test_only

# STOP_test_only



# START_test_only

# STOP_test_only



# START_test_only

# STOP_test_only



# START_test_only

# STOP_test_only


