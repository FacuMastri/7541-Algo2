EXEC = pruebas
ZIPFILE = abb

CC = gcc
CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
GDB_FLAGS = -quiet  -ex 'set pagination off' -ex 'set confirm off'

# Se puede comentar durante el desarrollo.
CFLAGS += -Werror

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
	$(CC) $(CFLAGS) abb.c pila.c pruebas_alumno.c main.c testing.c -o $(EXEC)

# Segundo set de pruebas.
test: abb_aux
	./abb_test.py

abb_aux: abb.o abb_aux.o

# Dependencias adicionales.
-include deps.mk

# Borrar archivos *.o generados.
clean:
	rm -f abb_aux *.o

.PHONY: test clean
