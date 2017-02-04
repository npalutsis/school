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
	// Creates a deck from 0-n
	for(int i = 0; i < n; i++)
		deck.push_back(i);
}

CardDeck::~CardDeck(){}

int CardDeck::getSize(){
	return deck.size();
}

// Shuffles deck
void CardDeck::shuffle(){
	random_shuffle(deck.begin(), deck.end());
}

// Detects if the deck is in order
int CardDeck::inOrder(){
	for(int i = 0; i < num-1; i++){
		if(deck[i] >= deck[i+1])
			return 0;
	}
	return 1;
}

ostream &operator<<(ostream &output, CardDeck &print){
	deque<int>::const_iterator i;
		for(i = print.deck.begin(); i != print.deck.end(); ++i)
		output << *i << ", ";
		output << endl;
	return(output);
}

// Prints out the order of the current deck
void CardDeck::printReverse(){
	deque<int>::const_reverse_iterator r;
	deque<int>::const_reverse_iterator end = deck.rend();
	for (r = deck.rbegin(); r != end; ++r) 
		cout << *r << ", ";

	cout << endl;
}

// Displays if the deck is in order
void CardDeck::printOrder(){
	if(inOrder())
		cout << "The deck is in order." << endl;
	else
		cout << "The deck is out of order." << endl;
}

// Shuffles until deck is in order
int CardDeck::monkeySort(){
	int count = 0;
	while(!inOrder()){
		this->shuffle();
		count++;
	}
	return count;
}

// Deals card to assigned player
int CardDeck::deal(int i, int disp, string player){ // deal(card in deck, display, which player)
	int card = deck[i] % 12;		// Gives value 2-9, ace, or face card
	int val;
	if(disp)		// displays what card was dealt
		display(card, player);
	else			// card was dealt face down
		cout << player << " was dealt a card face down." << endl;
	
	// Gives numerical value to card for the player's total
	if(card == 0)
		val = 11;
	else if(card >= 1 || card <= 9)
		val = card+1;
	else if(card >= 10 || card <=12)
		val = 10;
	return val;
}

// Displays which card was dealt
void CardDeck::display(int val, string player){
	switch(val){
		case 0:
			cout << player << " was dealt an ace." << endl;
			break;
		case 1:
			cout << player << " was dealt a two." << endl;
			break;
		case 2:
			cout << player << " was dealt a three." << endl;
			break;
		case 3:
			cout << player << " was dealt a four." << endl;
			break;
		case 4:
			cout << player << " was dealt a five." << endl;
			break;
		case 5:
			cout << player << " was dealt a six." << endl;
			break;
		case 6:
			cout << player << " was dealt a seven." << endl;
			break;
		case 7:
			cout << player << " was dealt an eight." << endl;
			break;
		case 8:
			cout << player << " was dealt a nine." << endl;
			break;
		case 9:
			cout << player << " was dealt a ten." << endl;
			break;
		case 10:
			cout << player << " was dealt a jack." << endl;
			break;
		case 11:
			cout << player << " was dealt a queen." << endl;
			break;
		case 12:
			cout << player << " was dealt a king." << endl;
			break;
	}
}













