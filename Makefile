CC=gcc
CFLAGS=-I -Ofast.
DEPS=main.c expr.h macros.h terms.h

OBJ := expr.o
OBJ += terms.o
OBJ += matrix.o
OBJ += poly.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

dexter: $(OBJ) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

run: dexter
	./dexter

clean:
	rm -f *.o dexter
