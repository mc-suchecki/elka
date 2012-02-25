CC=g++
CFLAGS=-Wall -pedantic
LFLAGS=
OBJS=main.o asd.o

pierscien: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o pierscien

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc -o main.o

asd.o: asd.cc ListMap.h
	$(CC) $(CFLAGS) -c asd.cc -o asd.o

clean:
	rm -f *.o
