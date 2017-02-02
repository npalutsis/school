#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include "CardDeck.h"

using namespace std;

CardDeck::CardDeck(int n){
	num = n;
	for(int i = 0; i < n; i++)
		deck.push_back(i);
}

int CardDeck::getSize(){
	return deck.size();
}

void CardDeck::shuffle(){
	random_shuffle(deck.begin(), deck.end());
}

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

void CardDeck::printReverse(){
	deque<int>::const_reverse_iterator r;
	deque<int>::const_reverse_iterator end = deck.rend();
	for (r = deck.rbegin(); r != end; ++r) 
		cout << *r << ", ";

	cout << endl;
}

void CardDeck::printOrder(){
	if(inOrder())
		cout << "The deck is in order." << endl;
	else
		cout << "The deck is out of order." << endl;
}

