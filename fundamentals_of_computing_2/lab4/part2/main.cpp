#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "CardDeck.h"

using namespace std;

int main () {
	srand (time(0));
	CardDeck Deck;

	cout << "The original deck is:" << endl;
	cout << Deck;
	Deck.printOrder();
	// using built-in random generator:
	
	cout << endl << "The deck in reverse is:" << endl;
	Deck.printReverse();
	Deck.printOrder();
	
	Deck.shuffle();
	
	cout << endl << "The shuffled deck is:" << endl;
	cout << Deck;
	Deck.printOrder();
	cout << "The size of the deck is: " << Deck.getSize() << endl;
	
	return 0;
}
