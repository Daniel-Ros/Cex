CC = gcc
AR = ar -rcs
FLAGS = -Wall -g
CFLAGS = -Wall -c -g
LFLAGS = -lm


all: graph

graph: libgraph.a main.o
	$(CC) $(FLAGS) main.o -o $@ -L. -lgraph $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

libgraph.a : mystring.o
	$(AR) libgraph.a $^

mystring.o: graph.c
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: clean

clean:
	rm -f *.o *.a *.so graph
