CC=gcc
CFLAGS=-I.

DEPS = main.h
OBJ = main.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

UROV: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core main
