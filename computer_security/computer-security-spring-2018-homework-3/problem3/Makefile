all: main

main: main.o
	gcc main.o -o main -lsodium

main.o: main.c
	gcc -Wall -g -c  main.c -o main.o

clean:
	rm -f main.o main
