CC = gcc
AR = ar -rcs
FLAGS = -Wall -c
LFLAGS = -lm


all: loops recursives recursived loopd maindloop maindrec mains

basicClassifications.o : basicClassification.c
	$(CC) $(FLAGS) $^ -o $@

basicClassificationd.o : basicClassification.c
	$(CC) $(FLAGS) -fPIC $^ -o $@

loops: libclassloops.a

libclassloops.a: basicClassifications.o advancedClassificationLoops.o
	$(AR) libclassloops.a $^

advancedClassificationLoops.o : advancedClassificationLoop.c
	$(CC) $(FLAGS) $^ -o $@

loopd:libclassloops.so

libclassloops.so: basicClassificationd.o advancedClassificationLoopd.o
	$(CC) -shared -o libclassloops.so $^

advancedClassificationLoopd.o : advancedClassificationLoop.c
	$(CC) $(FLAGS) -fPIC $^ -o $@

recursives:libclassrec.a

libclassrec.a: basicClassifications.o advancedClassificationRecursions.o
	$(AR) libclassrec.a $^

advancedClassificationRecursions.o : advancedClassificationRecursion.c
	$(CC) $(FLAGS) $^ -o $@

recursived:libclassrec.so

libclassrec.so: basicClassificationd.o advancedClassificationRecursion.o
	$(CC) -shared -o libclassrec.so $^

advancedClassificationRecursion.o : advancedClassificationRecursion.c
	$(CC) $(FLAGS) -fPIC $^ -o $@

mains: main.c recursives
	$(CC) $(FLAGS) main.c -o mains -L. -lclassrec $(LFLAGS)

maindloop: main.c loopd
	$(CC) $(FLAGS) main.c -o maindloop -L. -lclassloops $(LFLAGS)

maindrec:main.c recursives
	$(CC) $(FLAGS) main.c -o maindrec -L. -lclassrec $(LFLAGS)



.PHONY: clean

clean:
	rm -f *.o *.a *.so maindloop maindrec mains
