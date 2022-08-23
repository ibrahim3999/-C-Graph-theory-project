CC=gcc
Ar=ar
FLAGS = -Wall -g
OBJECT=main.o graph.o Algo.o

all: graph

graph: $(OBJECT)
	$(CC) $(FLAGS) -o graph $(OBJECT)
	
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

Algo.o: Algo.c graph.h
	$(CC) $(FLAGS) -c Algo.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so graph