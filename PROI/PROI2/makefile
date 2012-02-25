CC=g++
CFLAGS=-Wall -pedantic
LFLAGS=
OBJS=test.o

kolejka: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o kolejka

test.o: test.cpp kolejka.h
	$(CC) $(CFLAGS) -c test.cpp -o test.o

clean:
	rm -f *.o
