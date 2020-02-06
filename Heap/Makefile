EXEC = pruebas
ZIPFILE = heap

CC = gcc
CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
GDB_FLAGS = -quiet  -ex 'set pagination off' -ex 'set confirm off'

build: $(EXEC)

run: build
	./$(EXEC)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC)

gdb_tui: build
		gdb $(GDB_FLAGS) -tui ./$(EXEC)

zip: *
	zip -r $(ZIPFILE).zip . -x ".*" -x "*/.*"

$(EXEC): *.c
	$(CC) $(CFLAGS) *.c -o $(EXEC)
