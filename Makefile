CC=gcc
CFLAGS=-ansi -pedantic -std=c99
LDFLAGS=
EXEC=graph.exe

all: $(EXEC)

graph.exe: Graph.o Vector.o main.o Arrangement.o
	$(CC) -o $@ $^ $(LDFLAGS)

Graph.o: Graph/Graph.c Graph/Graph.h Graph/Arrangement.h
	$(CC) -o $@ -c $< $(CFLAGS)

Arrangement.o: Graph/Arrangement.c Graph/Arrangement.h
	$(CC) -o $@ -c $< $(CFLAGS)

Vector.o: Graph/Vector.c Graph/Vector.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c Graph/Graph.h Graph/Vector.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)