mortgage: main.o mortgage.o
	g++ -o mortgage main.o mortgage.o
 
main.o: main.cpp
	g++ -c main.cpp
 
mortgage.o: mortgage.cpp mortgage.cpp
	g++ -c mortgage.cpp
 
clean:
	rm mortgage *.o
