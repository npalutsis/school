/* Author: Nick Palutsis
   Date: April 3, 2016
   CSE 20212
   Lab 9 */
	
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "CardDeck.h"

using namespace std;

int main () {
	srand (time(0));
	CardDeck Deck(52);
	
	// Print orignal ordered deck
	cout << "The original deck is:" << endl;
	cout << Deck;
	Deck.printOrder();
	
	// Print ordered deck in reverse
	cout << endl << "The deck in reverse is:" << endl;
	Deck.printReverse();
	Deck.printOrder();
	
	Deck.shuffle();	// Shuffle deck
	
	// Print shuffled deck
	cout << endl << "The shuffled deck is:" << endl;
	cout << Deck;
	Deck.printOrder();
	cout << "The size of the deck is: " << Deck.getSize() << endl;
	
	return 0;
}
