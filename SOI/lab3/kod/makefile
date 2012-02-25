CC=gcc
CFLAGS=-Wall

all: semafor pisarz czytelnik clean

semafor: nadzorca.c bufor.h
	$(CC) $(LFLAGS) nadzorca.c -o semafory

pisarz: pisarz.c bufor.h
	$(CC) $(CFLAGS) pisarz.c -o pisarz

czytelnik: czytelnik.c bufor.h
	$(CC) $(CFLAGS) czytelnik.c -o czytelnik

clean:
	rm -f *.o
