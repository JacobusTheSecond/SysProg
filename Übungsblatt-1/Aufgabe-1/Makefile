CC=gcc
CFLAGS=-g -Wall
DEPS = personen_liste.h mystring.h
OBJ = dll.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dll: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
