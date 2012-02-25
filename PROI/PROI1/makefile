CC=g++
CFLAGS=-Wall -pedantic
LFLAGS=
OBJS=macierz.o test.o

macierze: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o macierze

test.o: test.cpp macierz.h
	$(CC) $(CFLAGS) -c test.cpp -o test.o

macierz.o: macierz.cpp macierz.h
	$(CC) $(CFLAGS) -c macierz.cpp -o macierz.o

clean:
	rm -f *.o
