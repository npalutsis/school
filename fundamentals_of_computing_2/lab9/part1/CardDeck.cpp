/* Author: Nick Palutsis
   Date: April 3, 2016
   CSE 20212
   Lab 9 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "CardDeck.h"

using namespace std;

CardDeck::CardDeck(int n){
	// Creates a newDeck from 0-n
	for(int i = 1; i <= n; i++)
		newDeck.pushBack(i);
}

CardDeck::~CardDeck(){}

int CardDeck::getSize(){
	return newDeck.getSize();
}

// Shuffles newDeck
void CardDeck::shuffle(){
	int temp;
	for ( int i = 1; i <= newDeck.getSize(); i++){
		int j = rand() % i;
		temp = newDeck.getVal(i);
		newDeck.setVal(i, newDeck.getVal(j));
		newDeck.setVal(j, temp);
	}
}

// Detects if the newDeck is in order
int CardDeck::inOrder(){
	for(int i = 0; i < newDeck.getSize() - 1; i++){
		if(newDeck.getVal(i) >= newDeck.getVal(i+1))
			return 0;
	}
	return 1;
}

ostream &operator<<(ostream &output, CardDeck &print){
	for(int i = 0; i < print.newDeck.getSize() - 1; ++i)
		output << print.newDeck.getVal(i) << ", ";
	output << print.newDeck.getVal(print.newDeck.getSize() - 1) << endl;
	return(output);
}

// Prints out the order of the current newDeck
void CardDeck::printReverse(){
	for (int i = newDeck.getSize() - 1; i > 0; i--) {
		cout << newDeck.getVal(i) << ", ";
	}
	cout << newDeck.getVal(0) << endl;
}

// Displays if the newDeck is in order
void CardDeck::printOrder(){
	if(inOrder())
		cout << "The deck is in order." << endl;
	else
		cout << "The deck is out of order." << endl;
}