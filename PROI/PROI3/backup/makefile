CC=g++
CFLAGS=-Wall -pedantic
LFLAGS=
OBJS=interfejs.o gui.o

interfejs: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gui

gui.o: gui.cpp interfejs.h
	$(CC) $(CFLAGS) -c gui.cpp -o gui.o

interfejs.o: interfejs.cpp interfejs.h
	$(CC) $(CFLAGS) -c interfejs.cpp -o interfejs.o

clean:
	rm -f *.o
