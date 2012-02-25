CC=gcc
CFLAGS=
LFLAGS=
OBJS=main.o lista.o tabela.o terminarz.o pliki.o

liga: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o liga

main.o: main.c liga.h
	$(CC) $(CFLAGS) -c main.c -o main.o

lista.o: lista.c liga.h
	$(CC) $(CFLAGS) -c lista.c -o lista.o

tabela.o: tabela.c liga.h
	$(CC) $(CFLAGS) -c tabela.c -o tabela.o

terminarz.o: terminarz.c liga.h
	$(CC) $(CFLAGS) -c terminarz.c -o terminarz.o

pliki.o: pliki.c liga.h
	$(CC) $(CFLAGS) -c pliki.c -o pliki.o

clean:
	rm -f *.o