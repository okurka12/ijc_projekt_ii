# Vit Pavlik
# login: xpavli0a
# osobni cislo: 251301
# fakulta: FIT VUT
# Created:  2022-04-03
# Modified: 2022-04-03
# vyvijeno s GNU Make 4.3 (Built for x86_64-pc-linux-gnu)

CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
# CFLAGS=-m32 -O0 -std=c11 -Wall -Wextra -pedantic -g

# START_test_only
PYTHON=python3
# STOP_test_only


tail: tail.c
	$(CC) $(CFLAGS) -o tail tail.c

clean:
	rm -f *.o *.elf



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


