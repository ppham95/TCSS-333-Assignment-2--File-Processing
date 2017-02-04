CC=gcc
LD=gcc
ifdef DEBUG
CFLAGS= -std=c99 -ggdb -Wall
else
CFLAGS= -std=c99 -O3
endif
LIBS= -lm

testArraysStrings: testArraysStrings.o arraysStrings.o arraysStrings.h vectors.o vectors.h
		$(LD) -o testArraysStrings arraysStrings.o testArraysStrings.o vectors.o $(LIBS)
		
testArraysStrings.o: testArraysStrings.c
		$(CC) $(CFLAGS) -o testArraysStrings.o -c testArraysStrings.c
		
arraysStrings.o: arraysStrings.c arraysStrings.h vectors.o vectors.h
		$(CC) $(CFLAGS) -o arraysStrings.o -c arraysStrings.c
   
vectors.o: vectors.c vectors.h
		$(CC) $(CFLAGS) -o vectors.o -c vectors.c
		
clean:
		rm *.o
		rm testArraysStrings

