all: main

main: main.o rational.o
	g++ main.o rational.o -o main

main.o: main.cpp
	g++ -c main.cpp

rational.o: rational.cpp rational.h
	g++ -c rational.cpp

clean:
	rm -f *.o *~ rational
