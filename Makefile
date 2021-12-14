CC = gcc
AR = ar -rcs
FLAGS = -Wall
CFLAGS = -Wall -c
LFLAGS = -lm


all: stringProg

stringProg: libstr.a main.o
	$(CC) $(FLAGS) main.o -o $@ -L. -lstr $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

libstr.a : mystring.o
	$(AR) libstr.a $^

mystring.o: mystring.c
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: clean

clean:
	rm -f *.o *.a *.so stringProg
