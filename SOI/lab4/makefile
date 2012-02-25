CC=g++
CFLAGS=-Wall -pthread

all: monitor

monitor: monitor.cpp monitor.h
	$(CC) $(CFLAGS) monitor.cpp -o monitory

clean:
	rm -f *.o
