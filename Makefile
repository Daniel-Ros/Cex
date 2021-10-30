CC = gcc 
AR = ar -rcs 
FLAGS = -Wall 
 
# all:

loops: basicClassification.c advancedClassificationLoop.c
	$(AR) libclassloops.a basicClassification.c advancedClassificationLoop.c

loopd: basicClassification.c advancedClassificationLoop.c
	$(CC) -c basicClassification.c advancedClassificationLoop.c -o libclassloops.so

# recursives:

# recursived:


# mains:

maindloop: main.c loopd
	$(CC) main.c -o maindloop -libclassloops

# maindrec:

.PHONY: clean 

clean: 
	rm -f *.o *.a *.so