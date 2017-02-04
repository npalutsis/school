/* Author: Nick Palutsis
   Date: April 3, 2016
   CSE 20212
   Lab 9 */
   
#ifndef CARD_DECK_H
#define CARD_DECK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "ndvector.h"

using namespace std;

class CardDeck {
	
	friend ostream &operator<<(ostream &, CardDeck &);
	
	public:
		CardDeck(int);
		~CardDeck();
		int getSize();
		void shuffle();
		int inOrder();
		void printReverse();
		void printOrder();
	private:
		NDVector<int> newDeck;
};

#endif