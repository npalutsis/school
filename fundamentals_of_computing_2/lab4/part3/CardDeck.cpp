/* Author: Nick Palutsis
	Date: February 16, 2016
	CSE 20212
	Lab 4 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include "CardDeck.h"

using namespace std;

CardDeck::CardDeck(int n){
	num = n;
	// pushes back to create a deck 0-n
	for(int i = 0; i < n; i++)
		deck.push_back(i);
}

CardDeck::~CardDeck(){}

int CardDeck::getSize(){
	return deck.size();
}

// shuffles deck
void CardDeck::shuffle(){
	random_shuffle(deck.begin(), deck.end());
}

// Detects if the deck is in increasing order
int CardDeck::inOrder(){
	for(int i = 0; i < num-1; i++){
		if(deck[i] >= deck[i+1])
			return 0;
	}
	return 1;
}

// prints out current deck order
ostream &operator<<(ostream &output, CardDeck &print){
	deque<int>::const_iterator i;
		for(i = print.deck.begin(); i != print.deck.end(); ++i)
		output << *i << ", ";
		output << endl;
	return(output);
}

// prints current order of the deck in reverse
void CardDeck::printReverse(){
	deque<int>::const_reverse_iterator r;
	deque<int>::const_reverse_iterator end = deck.rend();
	for (r = deck.rbegin(); r != end; ++r) 
		cout << *r << ", ";

	cout << endl;
}

// Displays if the deck is in order or not
void CardDeck::printOrder(){
	if(inOrder())
		cout << "The deck is in order." << endl;
	else
		cout << "The deck is out of order." << endl;
}

// shuffles the deck until the deck is in order
int CardDeck::monkeySort(){
	int count = 0;
	while(!inOrder()){
		this->shuffle();
		count++;		// number of shuffles
	}
	return count;
}

