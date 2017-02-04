all: cards

cards: main.o CardDeck.o
	g++ -o cards main.o CardDeck.o

main.o: main.cpp
	g++ -c main.cpp

CardDeck.o: CardDeck.cpp CardDeck.h
	g++ -c CardDeck.cpp

clean:
	rm -f *.o *~ cards
