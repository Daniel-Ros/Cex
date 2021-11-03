CC = gcc
AR = ar -rcs
FLAGS = -Wall
CFLAGS = -Wall -c
LFLAGS = -lm


all: loops recursives maindloop maindrec mains mainsloop recursived loopd

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

mains: main.o libclassrec.so
	$(CC) $(FLAGS) main.o -o $@ -L. ./libclassrec.so $(LFLAGS)

maindloop: main.o libclassloops.a
	$(CC) $(FLAGS) main.o -o $@ -L. ./libclassloops.a $(LFLAGS)

maindrec: main.o libclassrec.a
	$(CC) $(FLAGS) main.o -o $@ -L. ./libclassrec.a $(LFLAGS)

main.o: main.c NumClass.h
	$(CC) $(CFLAGS) main.c -o main.o


.PHONY: clean

clean:
	rm -f *.o *.a *.so maindloop maindrec mains
