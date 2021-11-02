CC = gcc
AR = ar -rcs
FLAGS = -Wall
CFLAGS = -Wall -c
LFLAGS = -lm


all: loops recursives recursived loopd maindloop maindrec mains mainsloop

basicClassifications.o : basicClassification.c
	$(CC) $(CFLAGS) $^ -o $@

basicClassificationd.o : basicClassification.c
	$(CC) $(CFLAGS) -fPIC $^ -o $@

loops: libclassloops.a

libclassloops.a: basicClassifications.o advancedClassificationLoops.o
	$(AR) libclassloops.a $^

advancedClassificationLoops.o : advancedClassificationLoop.c
	$(CC) $(CFLAGS) $^ -o $@

loopd:libclassloops.so

libclassloops.so: basicClassificationd.o advancedClassificationLoopd.o
	$(CC) -shared -o libclassloops.so $^

advancedClassificationLoopd.o : advancedClassificationLoop.c
	$(CC) $(CFLAGS) -fPIC $^ -o $@

recursives:libclassrec.a

libclassrec.a: basicClassifications.o advancedClassificationRecursions.o
	$(AR) libclassrec.a $^

advancedClassificationRecursions.o : advancedClassificationRecursion.c
	$(CC) $(CFLAGS) $^ -o $@

recursived:libclassrec.so

libclassrec.so: basicClassificationd.o advancedClassificationRecursion.o
	$(CC) -shared -o libclassrec.so $^

advancedClassificationRecursion.o : advancedClassificationRecursion.c
	$(CC) $(CFLAGS) -fPIC $^ -o $@

mains: main.o recursives
	$(CC) $(FLAGS) main.o -o mains -L. -lclassrec $(LFLAGS)

mainsloop :main.o loopd
	$(CC) $(FLAGS) main.o -o mainsloop -L. -lclassloops $(LFLAGS)

maindloop: main.o loopd
	$(CC) $(FLAGS) main.o -o maindloop -L. -lclassloops $(LFLAGS)

maindrec: main.o recursives
	$(CC) $(FLAGS) main.o -o maindrec -L. -lclassrec $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o


.PHONY: clean

clean:
	rm -f *.o *.a *.so maindloop maindrec mains
