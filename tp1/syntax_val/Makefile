EXEC = syntax_val

ZIPFILE = tp1
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
GDB_FLAGS = -quiet  -ex 'set pagination off' -ex 'set confirm off'

#Compilar.
build: $(EXEC)

#Correr.
run: build
	cat scripts1.txt | ./$(EXEC)

#Valgrindear.
valgrind: build
	valgrind $(VFLAGS) cat scripts1.txt | ./$(EXEC)

#Correr GDB con interfaz.
gdb_tui: build
		gdb $(GDB_FLAGS) -tui ./$(EXEC)

#Ver tiempo de ejecución.
runtime: build
		time ./$(EXEC)
#Zippear.
zip: *
	zip -r $(ZIPFILE).zip . -x ".*" -x "*/.*"

#Linker.
$(EXEC): *.c
	$(CC) $(CFLAGS) *.c -o $(EXEC)
