/* Author: Nick Palutsis
	Date: February 16, 2016
	CSE 20212
	Lab 4 */

#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "CardDeck.h"

using namespace std;

int main () {
	//srand (time(0));
	for(int i = 7; i <= 9; i++){		// Test for deck sizes of 7, 8, and 9
		for(int j = 0; j < 3; j++){	// Test each deck size 3 times
			CardDeck Deck(i);				// Create deck of size i
			Deck.shuffle();	// Initial shuffle
			// Return number of shuffles until ordered again
			cout << "Number of shuffles to order a deck of " << i << " cards: " << Deck.monkeySort() << endl;
		}
	}
		
	return 0;
}
