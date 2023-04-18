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

# poznamka: make preklada s -fPIC i pro statickou knihovnuc coz neni potreba
# ovsem Makefile by byl dvakrat delsi nez kdybych to tak neudelal

# ruzne kombinace definovanych symbolu
#CFLAGS=-fPIC -std=c11 -Wall -Wextra -pedantic -g -DNDEBUG
CFLAGS=-fPIC -std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG
#CFLAGS=-fPIC -std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG \
-HASHTEST
LDFLAGS=

# pro 32bit verzi odkomentovat nasledujici
#CFLAGS=-m32 -fPIC -std=c11 -Wall -Wextra -pedantic -g -DNDEBUG
#CFLAGS=-m32 -fPIC -std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG
#CFLAGS=-m32 -fPIC -std=c11 -Wall -Wextra -pedantic -g -DSTATISTICS -DNDEBUG \
-HASHTEST
#LDFLAGS=-m32

HTAB_MODULES=htab_bucket_count.o \
htab_clear.o \
htab_erase.o \
htab_find.o \
htab_for_each.o \
htab_free.o \
htab_free_list.o \
htab.h \
htab_hash.o \
htab_init.o \
htab_key_dtor.o \
htab_lookup_add.o \
htab_priv.h \
htab_size.o \
htab_statistics.o

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
libhtab.a: $(HTAB_MODULES)
	$(AR) r libhtab.a $(HTAB_MODULES)

# link shared library
libhtab.so: $(HTAB_MODULES)
	$(CC) $(LDFLAGS) -shared -fPIC -o libhtab.so $(HTAB_MODULES)

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

# ------------------------------------------------------------------------------
# here are all the modules for htab library
# ------------------------------------------------------------------------------

# compile htab_init
htab_init.o: htab_init.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_init.o htab_init.c

# compile htab_find
htab_find.o: htab_find.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_find.o htab_find.c

# compile htab_lookup_add
htab_lookup_add.o: htab_lookup_add.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_lookup_add.o htab_lookup_add.c

# compile htab_key_dtor
htab_key_dtor.o: htab_key_dtor.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_key_dtor.o htab_key_dtor.c

# compile htab_erase
htab_erase.o: htab_erase.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_erase.o htab_erase.c

# compile htab_key_dtor
htab_key_dtor.o: htab_key_dtor.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_key_dtor.o htab_key_dtor.c

# compile htab_clear
htab_clear.o: htab_clear.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_clear.o htab_clear.c

# compile htab_free_list
htab_free_list.o: htab_free_list.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_free_list.o htab_free_list.c

# compile htab_free
htab_free.o: htab_free.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_free.o htab_free.c

# compile htab_for_each
htab_for_each.o: htab_for_each.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_for_each.o htab_for_each.c

# compile htab_bucket_count
htab_bucket_count.o: htab_bucket_count.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_bucket_count.o htab_bucket_count.c

# compile htab_size
htab_size.o: htab_size.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_size.o htab_size.c

# compile htab_statistics
htab_statistics.o: htab_statistics.c htab_priv.h
	$(CC) $(CFLAGS) -c -o htab_statistics.o htab_statistics.c
