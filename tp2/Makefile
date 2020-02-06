EXEC = analog

ZIPFILE = tp2
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
GDB_FLAGS = -quiet  -ex 'set pagination off' -ex 'set confirm off'

#Compilar.
build: $(EXEC)

#Correr.
run: build
	./limite_memoria.sh ./$(EXEC) 

#Valgrindear.
valgrind: build
	valgrind $(VFLAGS) ./$(EXEC) 200

#Correr GDB con interfaz.
gdb_tui: build
		gdb $(GDB_FLAGS) -tui --args ./$(EXEC) 200

#Zippear.
zip: *
	zip -r $(ZIPFILE).zip . -x ".*" -x "*/.*"

#Linker.
$(EXEC): abb.c pila.c hash.c heap.c lista.c strutil.c tp2.c
	$(CC) $(CFLAGS) abb.c pila.c hash.c heap.c lista.c strutil.c tp2.c -o $(EXEC)
