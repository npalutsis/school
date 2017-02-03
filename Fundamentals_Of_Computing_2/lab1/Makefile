C4Game: C4Board.o main.o C4Col.o
	g++ -o C4Game main.o C4Col.o C4Board.o
 
main.o: main.cpp
	g++ -c main.cpp
	
C4Col.o: C4Col.cpp
	g++ -c C4Col.cpp

C4Board.io: C4Col.o C4Board.cpp
	g++ -c C4Board.cpp

clean:
	rm -f C4Game *.o
