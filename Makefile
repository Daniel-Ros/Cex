CC = gcc
AR = ar -rcs
FLAGS = -Wall
CFLAGS = -Wall -c
LFLAGS = -lm


all: main

main: libmat.a connections
	$(CC) $(FLAGS) main.o -o $@ -L. -lmat $(LFLAGS)

connections: main.c
	$(CC) $(CFLAGS) main.c -o main.o

libmat.a : my_mat.o
	$(AR) libmat.a $^

my_mat.o: my_mat.c
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: clean

clean:
	rm -f *.o *.a *.so maindloop maindrec mains