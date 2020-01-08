CC = g++
CFLAGS = -Wall -g --std=c++17

all: example.out

example.out: interp.o points.o example.o
	$(CC) $(CFLAGS) -o example.out example.o points.o interp.o

example.o: example.cpp
	$(CC) $(CFLAGS) -c example.cpp

points.o: points.cpp
	$(CC) $(CFLAGS) -c points.cpp

interp.o: interp.cpp
	$(CC) $(CFLAGS) -c interp.cpp

clean:
	rm -f *out *o *~
