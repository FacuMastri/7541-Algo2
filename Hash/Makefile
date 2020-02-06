EXEC = pruebas

ZIPFILE = hash
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
GDB_FLAGS = -quiet  -ex 'set pagination off' -ex 'set confirm off'

build: $(EXEC)

run: build
	./$(EXEC)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC)

gdb_tui: build
		gdb $(GDB_FLAGS) -tui ./$(EXEC)

runtime: build
		 ./tiempos_volumen.sh ./$(EXEC)

zip: *
	zip -r $(ZIPFILE).zip . -x ".*" -x "*/.*"

$(EXEC): *.c
	$(CC) $(CFLAGS) *.c -o $(EXEC)
