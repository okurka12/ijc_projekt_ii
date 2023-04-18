# Vit Pavlik
# login: xpavli0a
# osobni cislo: 251301
# fakulta: FIT VUT
# Created:  2022-04-03
# Modified: 2022-04-18
# vyvijeno s GNU Make 4.3 (Built for x86_64-pc-linux-gnu)

# archivar a prekladac
AR=ar
CC=gcc

# ruzne kombinace definovanych symbolu
#CFLAGS=-std=c11 -Wall -Wextra -pedantic -g -DNDEBUG
CFLAGS=-std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG
#CFLAGS=-std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG -HASHTEST
LDFLAGS=

# pro 32bit verzi odkomentovat nasledujici
#CFLAGS=-m32 -std=c11 -Wall -Wextra -pedantic -g -DNDEBUG
#CFLAGS=-m32 -std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG
#CFLAGS=-m32 -std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG -HASHTEST
#LDFLAGS=-m32


# make
.PHONY: all
all: tail wordcount wordcount-dynamic libhtab.a libhtab.so

# same as make clean; make
.PHONY: remake
remake: clean all

# smoketest wordcount and tail
.PHONY: run
run: tail wordcount wordcount-dynamic
	seq 1 3 | shuf | ./wordcount
	seq 1 3 | shuf | ./wordcount-dynamic
	seq 1 99 | ./tail -n 4


# compile + link tail
tail: tail.c
	$(CC) $(CFLAGS) -o tail tail.c

# archive static library
libhtab.a: htab_hash.o htab_utils.o
	$(AR) r libhtab.a htab_hash.o htab_utils.o

# link shared library
libhtab.so: htab_hash.o htab_utils.o
	$(CC) $(LDFLAGS) -shared -fPIC -o libhtab.so htab_hash.o htab_utils.o

# compile wordcount
wordcount.o: htab.h wordcount.c
	$(CC) $(CFLAGS) -c -o wordcount.o wordcount.c

# link wordcount-dynamic
wordcount-dynamic: wordcount.o libhtab.so io.o
	$(CC) $(LDFLAGS) -o wordcount-dynamic wordcount.o ./libhtab.so io.o

# link wordcount (static)
wordcount: wordcount.o libhtab.a io.o
	$(CC) $(LDFLAGS) -o wordcount wordcount.o libhtab.a io.o

# compile htab hash function module
htab_hash.o: htab_priv.h htab_hash.c
	$(CC) $(CFLAGS) -c -fPIC -o htab_hash.o htab_hash.c

# compile htab utilities module
htab_utils.o: htab_priv.h htab_utils.c
	$(CC) $(CFLAGS) -c -fPIC -o htab_utils.o htab_utils.c

# compile io.c
io.o: io.h io.c
	$(CC) $(CFLAGS) -c -o io.o io.c

# make clean
.PHONY: clean
clean:
	rm -f *.o *.elf *.so *.a tail wordcount wordcount-dynamic

# make the archive for submission
.PHONY: submit
submit:
	rm -f xpavli0a.zip
	dos2unix         *.c *.h Makefile
	zip xpavli0a.zip *.c *.h Makefile
	unix2dos         *.c *.h Makefile

# scp the archive to eva (scp prompts for password!)
.PHONY: scp_eva
scp_eva: submit
	scp xpavli0a.zip xpavli0a@eva.fit.vutbr.cz:~/ijc/xpavli0a.zip

