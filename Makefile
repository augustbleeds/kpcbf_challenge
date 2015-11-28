CC = g++
CFLAGS = -g -Wall

all: test1

test1: test1.o myHashMap.o
	$(CC) $(CFLAGS) test1.o myHashMap.o -o test1

test1.o: test1.cpp myHashMap.h
	$(CC) $(CFLAGS) -c test1.cpp

myHashMap.o: myHashMap.cpp myHashMap.h
	$(CC) $(CFLAGS) -c myHashMap.cpp

clean:
	rm -rf *.o test1